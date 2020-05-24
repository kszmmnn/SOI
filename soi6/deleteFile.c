#include "fs.h"

int deleteFile(char* name) {
	FILE *vd_file;
	superblock sb;
	node nd;
	uint address;
	int i;

	printf("usuwa %s \n", name);

	vd_file = fopen(VDname, "r+b");
	if (vd_file == NULL) {
		perror("unable to open VD\n");
		return -1;
	}

	if (fread(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("unable to read superblock");
		return -1;
	}

	address = 0;
	for (i = 0; i < sb.full_nodes; ++i) {
		if (fread(&nd, sizeof(node), 1, vd_file) != 1) {
			perror("unable to read node");
			return -1;
		}
		if (strcmp(nd.name, name) == 0) {
			break;
		}
	}
	address = ftell(vd_file) - sizeof(node);
	if (address == 0) {
		perror("no such file");
		return -1;
	}

	sb.free_space += nd.size;
	--sb.full_nodes;


	strcpy(nd.name, nilName);

	fseek(vd_file, 0, SEEK_SET);
	if (fwrite(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("error with writing superblock to disc");
		return -1;
	}

	fseek(vd_file, address, SEEK_SET);
	if (fwrite(&nd, sizeof(node), 1, vd_file) != 1) {
		perror("error with writing node to disc");
		return -1;
	}

	if (fclose(vd_file) != 0) {
		printf("Error with closing VD\n");
		return -1;
	}

	return 0;
}
