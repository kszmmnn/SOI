#ifndef PRODANCONS_H
#define PRODANCONS_H

#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include "buffer.h"

const int notsofast = 1; //seconds

void CreateProc(void (*func)(Buffer*), Buffer* b){
	int res = fork();
	if (res == 0 ){
		func(b);
		exit(0);
	}
}

void A1prod(Buffer* b){ //produce even mod 100 if less than 10 even
 while(1){
	sleep(notsofast);
	int n = rand()%50;
	n = n*2;
	b->l10e.p();
	put(b,n);

 }
}

void A2prod(Buffer* b){//produce odd mod 100 if more even than odd
 while(1){
	sleep(notsofast);
	int n = rand()%50;
	n=n*2+1;
	b->emo.p();
	put(b,n);
 }
}

void B1cons(Buffer* b){//consume even numbers if more than 3 numbers
 while(1){
	sleep(notsofast);
	if(getOddCnt(b) + getEvenCnt(b)>=7)
		b->sn.p();
	b->tn.p();
	b->eh.p();
	pop(b);
 }
}

void B2cons(Buffer* b){//consume odd numbers if more than 7 numbers
 while(1){
	sleep(notsofast);
	b->sn.p();
	b->tn.p();
	b->oh.p();
	pop(b);
 }
}

#endif
