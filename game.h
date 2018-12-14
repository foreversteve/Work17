#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

//Needed for sharedmemory
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

//Needed for semaphores
// #include <sys/types.h>
// #include <sys/ipc.h>
#include <sys/sem.h>

#include <errno.h>

#define KEY 0xFFFF
#define SHARED_KEY 0xF0F0
#define SEG_SIZE 200

void control(int argc, char *argv[]);