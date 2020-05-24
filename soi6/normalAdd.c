#include "fs.h"

int main() {

	createVD(5);
	map();
	copyToVD("plik1.txt");
	map();
	copyToVD("plik3.txt");
	map();
	view();
	deleteVD();


	return 0;
}
