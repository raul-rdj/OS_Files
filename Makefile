# makefile for scheduling program
#

# make fcfs - for FCFS scheduling


CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf fcfs
	


fcfs: driver.o list.o CPU.o schedule_fcfs.o
	$(CC) $(CFLAGS) -o fcfs driver.o schedule_fcfs.o list.o CPU.o


schedule_fcfs.o: schedule_fcfs.c
	$(CC) $(CFLAGS) -c schedule_fcfs.c

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

CPU.o: CPU.c cpu.h
	$(CC) $(CFLAGS) -c CPU.c
