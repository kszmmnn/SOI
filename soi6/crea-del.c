#include "fs.h"

int createVD(uint kibsize) {
	FILE *file;
	uint _size;
	uint _total_nodes;
	uint _full_nodes;
	uint _next_free_node;
	uint _next_free_addr;
	uint _free_space;

	uint sys_size;
	uint usr_size;
	uint nodeCnt;

	superblock sb;
	node nd;

	int i;

	_size = kibsize * 1024;
	sys_size = _size / 8;
	usr_size = _size - sys_size;

	nodeCnt = (sys_size - sizeof(superblock)) / sizeof(node);

	file = fopen(VDname, "wb+");
	if (file == NULL) {
		perror("unable to create VD\n");
		return -1;
	}

	fseek(file, _size - 1, SEEK_SET);


	_full_nodes = 0;
	_total_nodes = nodeCnt;
	_next_free_node = sizeof(sb);
	_next_free_addr = _size - usr_size;
	_free_space = _size - sys_size;

	sb.size = _size;
	sb.total_nodes = _total_nodes;
	sb.full_nodes = _full_nodes;
	sb.free_space = _free_space;
	sb.next_free_node = _next_free_node;
	sb.next_free_addr = _next_free_addr;

	fseek(file, 0, SEEK_SET);


	if (fwrite(&sb, sizeof(superblock), 1, file) != 1) {
		perror("error with writing superblock to disc");
		return -1;
	}

	strcpy(nd.name, nilName);
	nd.size = 0;
	nd.address = 0;

	for (i = 0; i < nodeCnt; ++i) {
		if (fwrite(&nd, sizeof(node), 1, file) != 1) {
			perror("error with writing node to disc");
			return -1;
		}
	}
	if (fclose(file) != 0) {
		printf("Error with closing VD\n");
		return -1;
	}
	return 0;
}

void deleteVD() {
	remove(VDname);
}
