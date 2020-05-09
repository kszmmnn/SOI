#include "src/lib/other/syscall.c"
#include "include/minix/type.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int i, j, iters, pri, grp;
	pid_t pid;
	message msg;
	pid = getpid();
	iters = 7;
	pri = atoi(argv[1]);
	grp = atoi(argv[2]);
	/*m1in1 -nr || m1in2 - value || m1in3 - pid*/
	/* 1-cuur
	 * 2- max
	 * 3-min
	 * 4-type
	 */



	 /*
	  rr
	  starzenie
	  sjf
	  */

	msg.m1_i1 = 1;
	msg.m1_i2 = pri;
	msg.m1_i3 = pid;
	_syscall(MM, SETPRI, &msg);


	msg.m1_i1 = 4;
	msg.m1_i2 = grp;
	msg.m1_i3 = pid;
	_syscall(MM, SETPRI, &msg);



	printf("zyje  %d \n", pid);

	for (i = 0; i < iters; ++i){
		printf("dzialam, pid = %d(pri = %d)\n", pid, pri);
		for (j = 0; j < 125000000; ++j);
	}

	printf("fin %d = pid\n", pid);
	return 0;
}
