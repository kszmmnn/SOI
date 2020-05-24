#include "fs.h"

int map(){
	FILE* vd_file;
	superblock sb;
	node temp;
	uint systemspace;
	int i;

	vd_file = fopen(VDname, "rb");
	if(vd_file == NULL){
		perror("unable to open VD\n");
		return -1;
	}

	fread(&sb, sizeof(superblock), 1, vd_file);

	systemspace = sb.total_nodes*sizeof(node) + sizeof(superblock);
	puts("");
	printf("total size: %d\n", sb.size);
	printf("free space: %d\n", sb.free_space);
	printf("total system space: %d\n", systemspace);
	printf("total user space: %d\n", sb.size - systemspace);
	puts("===================================================================");

	for(i=0; i<sb.total_nodes;++i){
		fread(&temp, sizeof(node), 1, vd_file);
		if(strcmp(temp.name, nilName) != 0 && temp.size != 0)
		printf("%s at %d | size: %d \n","allocated", temp.address, temp.size );
	}


	return 0;
}
