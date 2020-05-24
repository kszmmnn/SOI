#include "fs.h"

int copyToVD(char *name) {
	char c;
	FILE *vd_file;
	FILE *file;
	superblock sb;
	node temp;
	uint file_size;
	uint name_len;
	uint nodeAddr;
	int i;

	printf("kopiuje %s \n", name);

	vd_file = fopen(VDname, "r+b");
	if (vd_file == NULL) {
		perror("unable to open VD\n");
		return -1;
	}

	file = fopen(name, "r");
	if (file == NULL) {
		perror("unable to open copied file\n");
		return -1;
	}

	if (fread(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("unable to read superblock");
		return -1;
	}

	name_len = strlen(name);
	if (name_len >= NAME_SIZE) {
		fclose(vd_file);
		fclose(file);
		perror("too long filename");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (file_size == -1L) {
		perror("wrong file_size");
		return -1;
	}

	for (i = 0; i < sb.total_nodes; ++i) {
		if (fread(&temp, sizeof(node), 1, vd_file) != 1) {
			perror("unable to read node");
			return -1;
		}

		if (strcmp(temp.name, name) == 0) {
			perror("file with the same name already exists");
			return -1;
		}
	}
	if (sb.free_space < file_size) {
		perror("not enough space");
		return -1;
	}

	if (sb.full_nodes == sb.total_nodes) {
		perror("all nodes occupied");
		return -1;
	}


	nodeAddr = 0;
	/*there is free space and free nodes*/
	if ((sb.next_free_node > 0) && (sb.size - sb.next_free_addr > file_size)
			&& (sb.size > sb.next_free_node)) {

		fseek(vd_file, sb.next_free_node, SEEK_SET);
		nodeAddr = sb.next_free_node;
		sb.next_free_node += sizeof(node);

		if (fread(&temp, sizeof(node), 1, vd_file) != 1) {
			perror("unable to read empty node");
			return -1;
		}

		if (temp.address != 0) {
			perror("node is not empty file system corrupted");
			return -1;
		}

		temp.address = sb.next_free_addr;
		strcpy(temp.name, name);
		temp.size = file_size;

		sb.free_space -= file_size;
		sb.full_nodes += 1;
		sb.next_free_addr += file_size;

	} else {/*there is free space before the next_free_addr*/

		fseek(vd_file, sizeof(superblock), SEEK_SET);
		for (i = 0; i < sb.total_nodes; ++i) {
			fread(&temp, sizeof(node), 1, vd_file);
			if ((strcmp(temp.name, nilName) == 0) && (temp.size != 0)) { /*block is freed before*/
				if (temp.size >= file_size) {
					strcpy(temp.name, name);
					temp.size = file_size;
					sb.free_space -= file_size;
					sb.full_nodes += 1;
					nodeAddr = sizeof(superblock) + i * sizeof(node);
					break;
				}

			}
		}
	}

	if (nodeAddr == 0) {
		perror("nowhere to put file");
		return -1;
	}

	if (fseek(vd_file, 0, SEEK_SET)!=0){
		perror("failed to fseek");
		return -1;
	}

	if (fwrite(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("error with writing superblock to disc");
		return -1;
	}

	fseek(vd_file, nodeAddr, SEEK_SET);

	if (fwrite(&temp, sizeof(node), 1, vd_file) != 1) {
		perror("error with writing node to disc");
		return -1;
	}

	fseek(file, 0, SEEK_SET);

	fseek(vd_file, temp.address, SEEK_SET);

	c = fgetc(file);
	while (c != EOF) {
		fputc(c, vd_file);
		c = fgetc(file);
	}

	if (fclose(vd_file) != 0) {
		printf("Error with closing VD\n");
		return -1;
	}
	if (fclose(file) != 0) {
		printf("Error with closing file\n");
		return -1;
	}
	return 0;
}

int copyFromVD(char *name) {
	FILE *vd_file;
	FILE *file;
	superblock sb;
	node temp;
	uint addr;
	uint size;
	char c;
	int i;

	printf("kopiuje %s \n", name);

	vd_file = fopen(VDname, "rwb+");
	if (vd_file == NULL) {
		perror("unable to open VD\n");
		return -1;
	}

	file = fopen(name, "w+");
	if (file == NULL) {
		perror("unable to open/create file\n");
		return -1;
	}

	if (fread(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("unable to read node");
		return -1;
	}

	addr = 0;
	for (i = 0; i < sb.full_nodes; ++i) {
		if (fread(&temp, sizeof(node), 1, vd_file) != 1) {
			perror("unable to read node");
			return -1;
		}
		if (strcmp(temp.name, name) == 0) {
			addr = temp.address;
			size = temp.size;
			break;
		}
	}

	if (addr == 0) {
		perror("file address not found");
		return -1;
	}

	fseek(vd_file, addr, SEEK_SET);

	c = fgetc(vd_file);
	while (size != 0) {
		fputc(c, file);
		c = fgetc(vd_file);
		--size;
	}

	if (fclose(vd_file) != 0) {
		printf("Error with closing VD\n");
		return -1;
	}
	if (fclose(file) != 0) {
		printf("Error with closing file\n");
		return -1;
	}

	return 0;
}
