#include <stdio.h>			/* printf(3), perror(3) */
#include <sched.h>			/* sched_getscheduler(2), sched_get_priority_min(2), sched_get_priority_max(2) */
#include <sys/time.h>		/* getpriority(2) */
#include <sys/resource.h>	/* getpriority(2) */
#include <errno.h>			/* errno */

/* gcc -Wall -g scheduling.c -o scheduling */

int main() {
	int policy, priority, min, max;

	if ((policy = sched_getscheduler(0)) < 0) {
		perror("sched_getscheduler");
		return -1;
	}

	errno = 0;
	priority = getpriority(PRIO_PROCESS, 0);
	if (errno != 0) {
		perror("getpriority");
		return -1;
	}

	if ((min = sched_get_priority_min(policy)) < 0) {
		perror("sched_get_priority_min");
		return -1;
	}

	if ((max = sched_get_priority_max(policy)) < 0) {
		perror("sched_get_priority_max");
		return -1;
	}
	switch(policy) {
		case 0: printf("Scheduling policy: SCHED_OTHER.\n");		break;
		case 1: printf("Scheduling policy: SCHED_FIFO.\n");			break;
		case 2: printf("Scheduling policy: SCHED_RR.\n");			break;
		case 3: printf("Scheduling policy: SCHED_BATCH.\n");		break;
		case 5: printf("Scheduling policy: SCHED_IDLE.\n");			break;
		case 4: printf("Scheduling policy: SCHED_DEADLINE.\n");		break;
		default: printf("Scheduling policy: UNKNOWN.\n");			break;

	}
	
	printf("Scheduling priority: %d.\n", priority);
	printf("Scheduling priority (min, max): (%d, %d).\n", min, max);

   	return 0;
}
