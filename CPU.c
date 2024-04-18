/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

//added CPU time
int timeUnit = 0;


// run this task for the specified time howLong
void run(Task *task, int howLong) {
	//printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->arrivalTime, task->burst, howLong);
	printf("Running {%s} -----> ", task->name);
	timeUnit = timeUnit + howLong; //updates CPU time after running task
}
