#include "fs.h"

int main() {
	createVD(3);
	copyToVD("plik1.txt");
	map();
	copyToVD("plik1.txt");
	map();
	view();

	return 0;
}
