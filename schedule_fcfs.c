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

/**
 * Run the FCFS scheduler
 */
void schedule()
{
    Task *current;

    // sanity checker
    traverse(head);

    while (head != NULL) {
        current = selectNextTask();

        //run(current, current->burst);
	
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

void calculateCurrent(Task *task){
	printf("Calculated: %s\n", task->name);
}
