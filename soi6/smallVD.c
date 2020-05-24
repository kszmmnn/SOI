#include "fs.h"

int main() {

	createVD(3);
	copyToVD("plik1.txt");
	map();
	copyToVD("plik2.txt");
	map();
	copyToVD("plik3.txt");
	map();
	copyToVD("plik2.txt");
	map();
	copyToVD("plik22.txt");
	map();
	view();
	deleteVD();


	return 0;
}
