/*
===========================================================================================================================
Name : 20.c
Author : Hrushikesh Nakka
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 29rd Aug, 2024.
===========================================================================================================================
*/

/*
===========================================================================================================================
Name : 20.c
Author : Hrushikesh Nakka
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 28th Aug, 2024.
===========================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
int main() {
    
    int priority = getpriority(PRIO_PROCESS, getpid());
    printf("Current priority of process %d: %d\n", getpid(), priority);
    int newp = nice(5);
    printf("Current priority of process %d: %d\n", getpid(), newp);
}
