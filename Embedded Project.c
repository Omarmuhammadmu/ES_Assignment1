/*
 * File name: Embedded project.c
 * Description: Assignment 1
 * Author : Omar Muhammad
 */
 
 /*Note: By default the code is set to schedule using Rate Monotonic(RM)*/

#define _GNU_SOURCE
#include <stdio.h>		/* Used to use i/o functions*/
#include <stdlib.h>
#include <pthread.h>	/* Used to call threads management functions*/
#include <unistd.h>
#include <sched.h>		/* Used to set priorities*/
#include <time.h>		/* Used to use time functions*/

/*********************************************************************
 *                       Definitions                       
 *********************************************************************/

/*Defining period of each task in microseconds*/
#define T1_Period 100000
#define T2_Period 200000
#define T3_Period 300000

/*Define priority for each task*/
/** For the RM: T1_period = 3, T1_period = 2, T1_period = 1
 *  For the Different priority assignment: T1_period = 18, T1_period = 37, T1_period = 5
 *  For the RR: T1_period = 1, T1_period = 1, T1_period = 1
 * **/
#define T1_priority 3
#define T2_priority 2
#define T3_priority 1

/*Define N1 and N2 for each task*/
#define T1_N1 10000
#define T1_N2 1000

#define T2_N1 30000
#define T2_N2 1050

#define T3_N1 3200
#define T3_N2 8125

/*Scheduling method*/
/** For RM and different priorities : SCHED_FIFO
 *  For Round-Robin					: SCHED_RR **/
#define schedulingMethold SCHED_FIFO

/*********************************************************************
 *                       Function definitions                        
 *********************************************************************/
void timespec_add_us(struct timespec *t, long us)
{
	t->tv_nsec += us*1000;
	if (t->tv_nsec > 1000000000) 
	{
		t->tv_nsec = t->tv_nsec - 1000000000;
		t->tv_sec += 1;
	}
}

int timespec_cmp(struct timespec *a, struct timespec *b)
{ 
	if 		(a->tv_sec > b->tv_sec) return 1;
	else if (a->tv_sec < b->tv_sec) return -1;
	else if (a->tv_sec == b->tv_sec)
	{
		if (a->tv_nsec > b->tv_nsec) return 1;
		else if (a->tv_nsec == b->tv_nsec) return 0;
		else return -1;
	}
}

/*Functions to run in threads*/
void *T1_function(void)
{
	struct timespec now, next; /*Used to capture if a task missed its deadline*/
	int a, compareResult;
	/*Get time before execution so to add the period later and compare with the time after exection*/
	clock_gettime(CLOCK_REALTIME, &next);
	while(1) {
		/*Execute the task*/
		for (int i=0; i<T1_N1; i++)
		{
			for (int j=0; j<T1_N2; j++) 
			{a = j / 2;}
		}
		/*Add the period on the before execution time*/
		timespec_add_us(&next, T1_Period);
		/*Getting time at this moment*/
		clock_gettime(CLOCK_REALTIME, &now);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL); 
		compareResult = timespec_cmp(&now,&next);
		if(compareResult == 1)
		{
			printf("Task 1 | missed the deadline\n");
		}
		else
		{
			printf("Task 1 | met the deadline\n");	
		}
		
	}
}

void *T2_function(void)
{
	struct timespec now, next; /*Used to capture if a task missed its deadline*/
	int a, compareResult;
	/*Get time before execution so to add the period later and compare with the time after exection*/
	clock_gettime(CLOCK_REALTIME, &next);
	while(1) {
		/*Execute the task*/
		for (int i=0; i<T2_N1; i++)
		{
			for (int j=0; j<T2_N2; j++) 
			{a = j / 2;}
		}
		/*Add the period on the before execution time*/
		timespec_add_us(&next, T2_Period);
		/*Getting time at this moment*/
		clock_gettime(CLOCK_REALTIME, &now);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL); 
		compareResult = timespec_cmp(&now,&next);
		if(compareResult == 1)
		{
			printf("Task 2 | missed the deadline\n");
		}
		else
		{
			printf("Task 2 | met the deadline\n");	
		}
	} 
}

void *T3_function(void)
{
	struct timespec now, next; /*Used to capture if a task missed its deadline*/
	int a, compareResult;
	/*Get time before execution so to add the period later and compare with the time after exection*/
	clock_gettime(CLOCK_REALTIME, &next);
	while(1) {
		/*Execute the task*/
		for (int i=0; i<T3_N1; i++)
		{
			for (int j=0; j<T3_N2; j++) 
			{a = j / 2;}
		}
		/*Add the period on the before execution time*/
		timespec_add_us(&next, T3_Period);
		/*Getting time at this moment*/
		clock_gettime(CLOCK_REALTIME, &now);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL); 
		compareResult = timespec_cmp(&now,&next);
		if(compareResult == 1)
		{
			printf("Task 3 | missed the deadline\n");
		}
		else
		{
			printf("Task 3 | met the deadline\n");	
		}
	} 
}


/*********************************************************************
 *                       Main function                      
 *********************************************************************/
int main(int argc, char **argv)
{
	int th1,th2,th3;
    pthread_t thread1,thread2,thread3;
    pthread_attr_t myattr1,myattr2,myattr3;
    cpu_set_t cpu1,cpu2,cpu3;
    struct sched_param myparam;

	/*Initialization of thread attributes for thread 1*/
    pthread_attr_init(&myattr1);
    pthread_attr_setinheritsched(&myattr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&myattr1, schedulingMethold);
    CPU_ZERO(&cpu1);CPU_SET(1,&cpu1);
    pthread_attr_setaffinity_np(&myattr1,sizeof(cpu_set_t),&cpu1);
    myparam.sched_priority = T1_priority;
    pthread_attr_setschedparam(&myattr1, &myparam);
    
    /*Initialization of thread attributes for thread 2*/
    pthread_attr_init(&myattr2);
    pthread_attr_setinheritsched(&myattr2, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&myattr2, schedulingMethold);
    CPU_ZERO(&cpu2);CPU_SET(1,&cpu2);
    pthread_attr_setaffinity_np(&myattr2,sizeof(cpu_set_t),&cpu2);
    myparam.sched_priority = T2_priority ;
    pthread_attr_setschedparam(&myattr2, &myparam);
    
	/*Initialization of thread attributes for thread 3*/
    pthread_attr_init(&myattr3);
    pthread_attr_setinheritsched(&myattr3, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&myattr3, schedulingMethold);
    CPU_ZERO(&cpu3);CPU_SET(1,&cpu3);
    pthread_attr_setaffinity_np(&myattr3,sizeof(cpu_set_t),&cpu3);
    myparam.sched_priority = T3_priority ;
    pthread_attr_setschedparam(&myattr3, &myparam);
    
    /*Creating threads with specified attributes*/
    th1=pthread_create(&thread1,&myattr1,&T1_function,NULL);
    th2=pthread_create(&thread2,&myattr2,&T2_function,NULL);
    th3=pthread_create(&thread3,&myattr3,&T3_function,NULL);
    
	/*Clean up thread attributes*/
    pthread_attr_destroy(&myattr1);
    pthread_attr_destroy(&myattr2);
    pthread_attr_destroy(&myattr3);	
    
	/*wait for each thread to finish*/
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    
    return 0;
}
