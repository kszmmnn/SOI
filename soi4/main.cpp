#include "buff.h"
#include "prodancons.h"

const int a1cnt = 3;
const int a2cnt = 3;
const int b1cnt = 3;
const int b2cnt = 3;

int main() {
	Buffer buffer;
	int i;
	int cnt = a1cnt + a2cnt + b1cnt + b2cnt;
	pthread_t tid[cnt];

	for (i = 0; i < a1cnt; ++i) { //A1
		pthread_create(&(tid[i]), NULL, producentA1, &buffer);

	}
	for (i = a1cnt; i < a1cnt + a2cnt; ++i) { //A2
		pthread_create(&(tid[i]), NULL, producentA2, &buffer);

	}
	for (i = a1cnt + a2cnt; i < a1cnt + a2cnt + b1cnt; ++i) { //B1
		pthread_create(&(tid[i]), NULL, consumerB1, &buffer);

	}

	for (i = a1cnt + a2cnt + b1cnt; i < cnt; ++i) { //B2
		pthread_create(&(tid[i]), NULL, consumerB2, &buffer);

	}
#ifndef SEE
	i = 65;
	while (i != 0) {
		buffer.show();
		sleep(1);
		--i;
	}
#endif

	for (i = 0; i < cnt; i++)
		pthread_join(tid[i], (void**) NULL);

	return 0;
}

