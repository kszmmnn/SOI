#ifndef FS_H_
#define FS_H_

#include <stdio.h>
#include <string.h>

#define MIN_SIZE 3
#define MAX_SIZE 100


#define NAME_SIZE 32

typedef unsigned int uint;

static const char* VDname = "VD";
static const char* nilName = "*nil*";



typedef struct superblock {
	uint size;
	uint total_nodes;
	uint full_nodes;
	uint free_space;
	uint next_free_node;
	uint next_free_addr;

} superblock;

typedef struct node {
	char name[NAME_SIZE];
	uint size;
	uint address;

} node;

int createVD(uint);
void deleteVD();

int copyToVD(char*);
int copyFromVD(char*);

int deleteFile(char*);

int map(void);

int view(void);

#endif /* FS_H_ */
