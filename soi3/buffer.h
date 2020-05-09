#ifndef Buffer_H
#define Buffer_H

#include <sys/shm.h>
#include "sema.h"

#include <iostream>

const int size = 100;

struct Buffer {
	Semaphore l10e;  //less 10 even
	Semaphore emo;   //even more than odd
	Semaphore tn;	 //three numbers in buff
	Semaphore sn;	 //seven numbers in buff
	Semaphore oh;	 //odd head
	Semaphore eh;	 //even head
	Semaphore sem;	 //buff lock
	Semaphore full;  //occupied cells
	Semaphore empty; //empty cells

	int putPos;
	int takePos;

	int odd;
	int even;
	int queue[size];

};


int lookFirst(Buffer *b) {
	int ret;
	b->sem.p();
	ret = b->queue[b->takePos];
	b->sem.v();
	return ret;
}

int getOddCnt(Buffer *b) {
	int ret;
	b->sem.p();
	ret = b->odd;
	b->sem.v();
	return ret;
}

int getEvenCnt(Buffer *b) {
	int ret;
	b->sem.p();
	ret = b->even;
	b->sem.v();
	return ret;
}

Buffer* createBuffer() {
	int shmid = shmget(IPC_PRIVATE, sizeof(Buffer), IPC_CREAT);
	if (shmid == -1) {
		throw "can't create Buffer";
	}
	Buffer *ret = (Buffer*) shmat(shmid, NULL, 0);

	if (ret == NULL) {
		throw "can't join Buffer";
	}
	return ret;
}

void setBuffer(Buffer *b) {
	b->putPos = 0;
	b->takePos = 0;
	b->odd=0;
	b->even=0;

	b->l10e = Semaphore(10);  	 //less than 10 even elements
	b->emo = Semaphore(0);	   	 //even more than odd
	b->tn = Semaphore(0);		 //three in buf
	b->sn = Semaphore(0);		 //seven in buf
	b->oh = Semaphore(0); 	  	 //odd head
	b->eh = Semaphore(0); 	  	 //even head
	b->sem = Semaphore(1);	  	 //buff lock
	b->full = Semaphore(0); 	 //occupied cells
	b->empty = Semaphore(size);  //free cells

}

void put(Buffer *b, int x) {
	b->sem.p();
	b->empty.p();

	if (x % 2 == 0) {
		++b->even;
	} else
		++b->odd;

	if(b->putPos == b->takePos){
		if(x%2==0)
			b->eh.v();
		else
			b->oh.v();
	}

	if(b->odd + b->even >=3)
		b->tn.v();
	if(b->odd + b->even >=7)
			b->sn.v();

	if(b->odd < b->even)
		b->emo.v();

	b->queue[b->putPos] = x;
	b->putPos = (b->putPos + 1) % size;

	b->full.v();
	b->sem.v();
}

int pop(Buffer *b) {
	int ret;
	b->sem.p();
	b->full.p();

	ret = b->queue[b->takePos];
	b->queue[b->takePos] = -1; //just for visualisation
	b->takePos = (b->takePos + 1) % size;
	if (ret%2 == 0){
		--b->even;
		b->l10e.v();
	}
	else
		--b->odd;


	if(b->takePos != b->putPos){
		if(b->queue[b->takePos]%2==0)
				b->eh.v();
		else
			b->oh.v();
	}

	b->empty.v();
	b->sem.v();
	return ret;
}





void printBuff(Buffer *b) {
	for (int i = 0; i < size; ++i)
		std::cout << b->queue[i] <<"|";
	std::cout << "\n";
}
#endif
