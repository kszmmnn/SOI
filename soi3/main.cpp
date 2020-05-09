#include "buffer.h"
#include "prodancons.h"
#include<sys/wait.h>

int main() {
	srand(time(NULL));

	Buffer *buf = createBuffer();
	setBuffer(buf);

	void (*p)(Buffer *b);

	p = A1prod;
	CreateProc(p, buf);
	p = A2prod;
	CreateProc(p, buf);

	p = B1cons;
	CreateProc(p, buf);
	p = B2cons;
	CreateProc(p, buf);

	while (1) {
		sleep(1);
		printBuff(buf);
	}

	while (wait(NULL) > 0)
		;
}
