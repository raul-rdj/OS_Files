/**
 * Implementation of various scheduling algorithms.
 *
 * FCFS scheduling
 */

#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list
struct node *head = NULL;

// sequence counter of next available thread identifier
int nextTid = 0;

Task *selectNextTask();

extern int timeUnit, idleTime;//CPU and idle time

// add a new task to the list of tasks
void add(char *name, int arrivalTime, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));

    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->arrivalTime = arrivalTime;
    newTask->burst = burst;

    // insert the new task into the list of tasks
    insert(&head, newTask);
}

//Function for calculations of current task
void calculateCurrent(Task *task){
	//initializations:
	static int turnAroundTime = 0;
	static int waitingTime = 0;
	static int responseTime = 0;
	static int processCount = 0;
	static int sumBurst = 0;

	//calculations
	int currentTurnAroundTime = timeUnit - task->arrivalTime;
	int currentWaitingTime = currentTurnAroundTime - task->burst;
	int currentResponseTime = (timeUnit - task->burst) - task->arrivalTime;
	float responseRatio = (float)(currentWaitingTime + task->burst)/task->burst;

	turnAroundTime = turnAroundTime + currentTurnAroundTime;
	waitingTime = waitingTime + currentWaitingTime;
	responseTime = responseTime + currentResponseTime;
	processCount++;
	sumBurst = sumBurst + task->burst;

	printf("%5s%20d%20d%20d%20.2f\n", task->name, currentTurnAroundTime, currentWaitingTime, currentResponseTime, responseRatio);

	//Calculating averages/throughput/cpu utilization when on last task
	if(head->next == NULL){
		float avgTT = (float)turnAroundTime/processCount;
		float avgWT = (float)waitingTime/processCount;
		float avgRT = (float)responseTime/processCount;	
		float throughput = (float)sumBurst / processCount;
		float cpuUtil = (float)(timeUnit - idleTime)/timeUnit;
		
		printf("\n-----AVERAGES-----\n");
		printf("Average TT:->[%.2f]\n", avgTT);
		printf("Average WT:->[%.2f]\n", avgWT);
		printf("Average RT:->[%.2f]\n", avgRT);
		printf("Throughput:->[%.2f]\n", throughput);
		printf("CPU Util---->[%.2f%%]\n", cpuUtil * 100);

	}
}

/**
 * Run the FCFS scheduler
 */
void schedule()
{
    Task *current;

    // sanity checker
    traverse(head);
	
    //print column titles here
    printf("\n-----CALCULATIONS-----\n");
    printf("           %5s%20s%20s%20s%20s\n", "Task", "Turnaround Time", "Waiting Time", "Response Time", "Response Ratio");

    while (head != NULL) {
        current = selectNextTask();

	//check whether the current task has arrived
	if(timeUnit < current->arrivalTime){
		idleTime = idleTime + (current->arrivalTime - timeUnit);
		timeUnit = current->arrivalTime;
	}

        run(current, current->burst);
	
	//run calculations for current task
	calculateCurrent(current);

        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run.
 */
Task *selectNextTask()
{
    return head->task;
}


