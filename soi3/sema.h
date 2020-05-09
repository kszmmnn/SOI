#ifndef SEMA_H
#define SEMA_H

#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>

class Semaphore {
public:

	Semaphore(int value) {
		if (sem_init(&sem, 1, value) != 0)
			throw "sem_init: failed";
	}
	~Semaphore() {

		sem_destroy(&sem);
	}

	void p() {

		if (sem_wait(&sem) != 0)
			throw "sem_wait: failed";
	}

	void v() {
		if (sem_post(&sem) != 0)
			throw "sem_post: failed";
	}

private:
	sem_t sem;
};

#endif
