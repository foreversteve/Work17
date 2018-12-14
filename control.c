
#include "game.h"

void control(int argc, char *argv[]){
	char cmd[3];
	cmd[2] = 0;
	if (argc > 1){
		strcpy(cmd,argv[1]);
	}
	else{
		printf("No input given...moving on\n");
		return;
	}
	//Shared Memory
	int shmd;
	char *data;

	shmd = shmget(SHARED_KEY, SEG_SIZE, IPC_CREAT | 0644);
	data = shmat(shmd,0 ,0);
	//Semaphore
	int semd = semget(KEY,1,IPC_CREAT | IPC_EXCL | 0644);
	if (strcmp(cmd,"-c")==0){
		if (semd == -1){
			printf("error is: %s\n",strerror(errno));
			// semd = semget(KEY,1,0);
			// v = semctl(semd, 0, GETVAL, 0);
			// printf("semct returns: %d\n",v);
		}
		else{
			union semun us;
			us.val = 2;
			int r = semctl(semd,0,SETVAL, us);
		}
		//Open File
		int fd;
		fd = open("story.txt",O_TRUNC|O_WRONLY|O_CREAT, 0666);

	}
	if (strcmp(cmd,"-r")==0){
		//Shared Mem:
		shmctl(shmd,IPC_RMID,0);
		printf("Shared Memory deleted\n");
		//Semaphore:

		if (semctl(semd,0,IPC_RMID,0) != -1){
			printf("Semaphore removed\n");
		}
		else{
			printf("error is: %s\n",strerror(errno));
		}
		//File:
		remove("story.txt");
	}
	if (strcmp(cmd,"-v")==0){
		char bucket[1000];
		int fd = open("story.txt",O_RDONLY);
		read(fd,bucket,1000);
		printf("Content of Story is:%s\n",bucket);
		close(fd);
	}

}


