#include "monitor.h"
#include <iostream>
#include <queue>
#include <pthread.h>

#ifndef BUFF_H_
#define BUFF_H_

const int size = 100;

int a1 = -2;
int a2 = -1;

class Buffer: public Monitor {
protected:

	std::queue<int> queue;
	int oddCnt;
	int evenCnt;
	Condition less_10_even; 		//A1  less 10 even
	Condition more_even;			//A2 even more than odd
	Condition three_nums;			//B1 three numbers in buff
	Condition seven_nums;			//B2 seven numbers in buff
	Condition even_head;			//B1 even head
	Condition odd_head;				//B2 odd head
	Condition full;					//occupied cells
	Condition empty;				//empty cells

public:
	Buffer() :
			oddCnt(0), evenCnt(0) {
	}

	void putEven() {
		enter();
		if (queue.size() >= size)
			wait(empty);
		if (evenCnt >= 10)
			wait(less_10_even);

		a1 = (a1 + 2) % 100;
		put(a1);

		if (queue.size() == 1)
			signal(even_head);
		signal(full);
		leave();
	}

	void putOdd() {
		enter();
		if (queue.size() >= size)
			wait(empty);
		if (evenCnt <= oddCnt)
			wait(more_even);

		a2 = (a2 + 2) % 100;
		put(a2);

		if (queue.size() == 1)
			signal(odd_head);
		signal(full);
		leave();
	}


	int getEven() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(full);
		if (queue.front() % 2 == 1)
			wait(even_head);
		if (queue.size() < 3)
			wait(three_nums);

		res = get();

		if (queue.front() % 2 == 1)
			signal(odd_head);
		leave();
		return res;
	}

	int getOdd() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(full);
		if (queue.front() % 2 == 0)
			wait(odd_head);
		if (queue.size() < 7)
			wait(seven_nums);

		res = get();

		if (queue.front() % 2 == 0)
			signal(even_head);
		leave();
		return res;
	}
	int lookFirst() {
		int res;
		enter();
		if (queue.size() == 0)
			wait(full);
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
			signal(more_even);
		if (queue.size() > 7)
			signal(seven_nums);
		else if (queue.size() > 3)
			signal(three_nums);
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

#endif /* BUFF_H_ */
