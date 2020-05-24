#include "fs.h"

int main() {

	createVD(3);
	copyToVD("plik1.txt");
	map();
	copyToVD("plik2.txt");
	map();
	copyToVD("plik3.txt");
	map();
	deleteFile("plik2.txt");
	map();
	copyToVD("plik22.txt");/*sizeof(plik22) < sizeof(plik2)*/
	map();
	view();
	deleteVD();


	return 0;
}
