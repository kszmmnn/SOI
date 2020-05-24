#include "fs.h"

int main() {

	createVD(3);
	map();
	copyToVD("bigfile.txt");
	map();
	view();
	deleteVD();


	return 0;
}
