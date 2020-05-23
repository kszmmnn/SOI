#include "buff.h"

#ifndef PRODANCONS_H_
#define PRODANCONS_H_

//#define SEE
//if commented changes the way buffer is displayed

#define ELEM_COUNT 10  //produced elements

void* producentA1(void *p) { //produce even mod 100 if less than 10 even
	std::cout << "Producent starts a1\n" << std::endl;

	Buffer *buffer = (Buffer*) p;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		buffer->putEven();
		sleep(1);

		#ifdef SEE
		int put = a1;
		std::cout << "adds " << put << std::endl;
		#endif

	}
	std::cout << "Producent ends a1\n" << std::endl;
	return 0;
}

void* producentA2(void *p) { //produce odd mod 100 if more even than odd
	std::cout << "Producent starts a2\n" << std::endl;

	Buffer *buffer = (Buffer*) p;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		buffer->putOdd();
		sleep(1);

		#ifdef SEE
		int put = a2;
		std::cout << "adds " << put << std::endl;
		#endif

	}
	std::cout << "Producent ends a2\n" << std::endl;
	return 0;
}

void* consumerB1(void *p) { //consume even numbers if more than 3 numbers
	std::cout << "consumer starts b1\n" << std::endl;

	Buffer *buffer = (Buffer*) p;
	int got = 0;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		sleep(1);
		got = buffer->getEven();

		#ifdef SEE
		std::cout << "gets " << got << std::endl;
		#endif

	}
	std::cout << "consumer ends b1\n" << std::endl;

	return 0;

}

void* consumerB2(void *p) { //consume odd numbers if more than 7 numbers
	std::cout << "consumer starts b2\n" << std::endl;

	Buffer *buffer = (Buffer*) p;
	int got = 0;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		sleep(1);
		got = buffer->getOdd();

		#ifdef SEE
		std::cout << "gets " << got << std::endl;
		#endif

	}
	std::cout << "consumer ends b2\n" << std::endl;
	return 0;
}

#endif /* PRODANCONS_H_ */
