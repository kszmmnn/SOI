#include "monitor.h"
#include <iostream>
#include <queue>
#include <atomic>

#define CONS_COUNT 20  //liczba konsumentow
#define ELEM_COUNT 100  //liczba produkowanych elementow

const int a1cnt = 2;
const int a2cnt = 0;
const int b1cnt = 1;
const int b2cnt = 0;

const int size = 100;

int a1(-2);
int a2(-1);

class Buffer: public Monitor {
protected:

	std::queue<int> queue;
	int oddCnt;
	int evenCnt;
	Condition l10e;
	Condition emo;
	Condition tn;
	Condition sn;
	Condition oh;
	Condition eh;
	Condition fullCond;
	Condition emptyCond;

	//less 10 even
	//even more than odd
	//three numbers in buff
	//seven numbers in buff
	//odd head
	//even head
	//occupied cells
	//empty cells
public:
	Buffer() :
			oddCnt(0), evenCnt(0) {
	}


	void putEven() {
		enter();
		if (queue.size() >= size)
			wait(emptyCond);
		if (evenCnt >= 10)
			wait(l10e);

		a1 = (a1+2)%100;
		put(a1);

		if (queue.size() == 1)
			signal(eh);
		signal(fullCond);
		leave();
	}

	void putOdd() {
		enter();
		if (queue.size() >= size)
			wait(emptyCond);
		if (evenCnt <= oddCnt)
			wait(emo);

		a2=(a2+2)%100;
		put(a2);

		if (queue.size() == 1)
			signal(oh);
		signal(fullCond);
		leave();
	}
	int getOdd() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(fullCond);
		if (queue.front() % 2 == 0)
			wait(oh);
		if (queue.size() < 7)
			wait(sn);

		res = get();

		if (queue.front() % 2 == 0)
			signal(eh);
		leave();
		return res;
	}

	int getEven() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(fullCond);
		if (queue.front() % 2 == 1)
			wait(eh);
		if (queue.size() < 3)
			wait(tn);
		res = get();

		if (queue.front() % 2 == 1)
			signal(oh);
		leave();
		return res;
	}

	int lookFirst() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(fullCond);
		res = queue.front();
		leave();
		return res;
	}

	int getEvenCnt() {
		enter();
		int res = evenCnt;
		leave();
		return res;
	}

	int getOddCnt() {
		enter();
		int res = oddCnt;
		leave();
		return res;
	}

	void show() {
		std::queue<int> q = queue;
		std::cout << std::endl;
		while (!q.empty()) {
			std::cout << q.front() << "|";
			q.pop();
		}
		std::cout << std::endl;
	}

private:
	void put(int x) {
		if (x % 2 == 0)
			++evenCnt;
		else
			++oddCnt;
		queue.push(x);

		if (evenCnt > oddCnt)
			signal(emo);
		if (queue.size() > 7)
			signal(sn);
		else if(queue.size() > 3)
			signal(tn);
	}

	int get() {
		int res;
		res = queue.front();
		queue.pop();
		if (res % 2 == 0)
			--evenCnt;
		else
			--oddCnt;
		return res;
	}

};

Buffer buffer;

void* producentA1(void*) { //produce even mod 100 if less than 10 even
	std::cout << "Producent uruchomiony a1\n" << std::endl;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		buffer.putEven();
		int put = a1;
		std::cout << "dodaje " << put << " " << pthread_self() << std::endl;
		sleep(1);
	}
	std::cout << "Producent konczy a1\n" << std::endl;
	return 0;
}

void* producentA2(void*) { //produce odd mod 100 if more even than odd
	std::cout << "Producent uruchomiony a2\n" << std::endl;
	for (int i = 1; i <= ELEM_COUNT; ++i) {

		buffer.putOdd();
		int put=a2;
		std::cout << "dodaje " << put << " " << pthread_self() << std::endl;
		sleep(1);
	}
	std::cout << "Producent konczy a2\n" << std::endl;
	return 0;
}

void* konsumentB1(void*) { //consume even numbers if more than 3 numbers
	std::cout << "konsument zaczyna b1\n" << std::endl;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		buffer.getEven();
		sleep(1);
	}
	std::cout << "konsument konczy b1\n" << std::endl;

	return 0;

}

void* konsumentB2(void*) { //consume odd numbers if more than 7 numbers
	std::cout << "konsument zaczyna b2\n" << std::endl;
	for (int i = 1; i <= ELEM_COUNT; ++i) {
		buffer.getOdd();
		sleep(1);
	}
	std::cout << "konsument konczy b2\n" << std::endl;
	return 0;
}

int main() {
	int i;
	pthread_t tid[40];

	//A1
	pthread_create(&(tid[0]), NULL, producentA1, 0);
	pthread_create(&(tid[1]), NULL, producentA1, 0);
	pthread_create(&(tid[2]), NULL, producentA1, 0);
	pthread_create(&(tid[3]), NULL, producentA1, 0);
//	pthread_create(&(tid[4]), NULL, producentA1, 0);
//	pthread_create(&(tid[5]), NULL, producentA1, 0);
//	pthread_create(&(tid[6]), NULL, producentA1, 0);
//	pthread_create(&(tid[7]), NULL, producentA1, 0);

	//A2
	pthread_create(&(tid[10]), NULL, producentA2, 0);
	pthread_create(&(tid[11]), NULL, producentA2, 0);
	pthread_create(&(tid[12]), NULL, producentA2, 0);
	pthread_create(&(tid[13]), NULL, producentA2, 0);
//	pthread_create(&(tid[14]), NULL, producentA2, 0);
//	pthread_create(&(tid[15]), NULL, producentA2, 0);
//	pthread_create(&(tid[16]), NULL, producentA2, 0);
//	pthread_create(&(tid[17]), NULL, producentA2, 0);
//

	//B1
	pthread_create(&(tid[20]), NULL, konsumentB1, 0);
	pthread_create(&(tid[21]), NULL, konsumentB1, 0);
	pthread_create(&(tid[22]), NULL, konsumentB1, 0);
//	pthread_create(&(tid[23]), NULL, konsumentB1, 0);
//	pthread_create(&(tid[24]), NULL, konsumentB1, 0);
//	pthread_create(&(tid[25]), NULL, konsumentB1, 0);
//	pthread_create(&(tid[26]), NULL, konsumentB1, 0);
//	pthread_create(&(tid[27]), NULL, konsumentB1, 0);

	//B2
	pthread_create(&(tid[30]), NULL, konsumentB2, 0);
	pthread_create(&(tid[31]), NULL, konsumentB2, 0);
	pthread_create(&(tid[32]), NULL, konsumentB2, 0);
//	pthread_create(&(tid[33]), NULL, konsumentB2, 0);
//	pthread_create(&(tid[34]), NULL, konsumentB2, 0);
//	pthread_create(&(tid[35]), NULL, konsumentB2, 0);
//	pthread_create(&(tid[36]), NULL, konsumentB2, 0);
//	pthread_create(&(tid[37]), NULL, konsumentB2, 0);






	i = 50;
	while (i != 0) {
		buffer.show();
		sleep(1);
		--i;
	}

	//czekaj na zakonczenie watkow
	for (i = 0; i < CONS_COUNT + 1; i++)
		pthread_join(tid[i], (void**) NULL);

	return 0;
}

