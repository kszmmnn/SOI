#include "fs.h"

int view(){
	FILE* vd_file;
	superblock sb;
	node nd;
	int i;

	vd_file = fopen(VDname, "rwb+");
	if (vd_file == NULL) {
		perror("unable to open VD\n");
		return -1;
	}

	if (fread(&sb, sizeof(superblock), 1, vd_file) != 1) {
		perror("unable to read superblock");
		return -1;
	}

	puts("");
	for (i = 0; i < sb.total_nodes; ++i) {
		if (fread(&nd, sizeof(node), 1, vd_file) != 1) {
			perror("unable to read node");
			return -1;
		}
		if (strcmp(nd.name, nilName) != 0) {
		printf("%s \n",nd.name);

		}
	}

	return 0;
}
