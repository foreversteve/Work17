

#include "game.h"

int main(){
	// get semaphores
	// see if it's > 0
	// if so:
	// 	display last line
	// else:
	// 	print "this is new"
	// prompt user input
	// read until new line
	// write it to file
	// close file
	// update sharedmemory
	int semd;
	int r;
	int v;

	semd = semget(KEY,1,IPC_CREAT | IPC_EXCL | 0644);
	if (semd == -1){
		// printf("error is: %s\n",strerror(errno));
		// semd = semget(KEY,1,0);
		// v = semctl(semd, 0, GETVAL, 0);
		printf("Access Denied\n");
		return 0;
	}
	else{
		// union semun us;
		// us.val = 1;
		// r = semctl(semd,-1,SETVAL, us);

		// -1 on semaphore
		char *data;
		struct sembuf buf;
		buf.sem_num = 0;
		buf.sem_op = -1;
		buf.sem_flg = SEM_UNDO;
		semop(KEY, &buf, 1);
		//Display shared memory
		int shmd;
		shmd = shmget(SHARED_KEY, SEG_SIZE, IPC_CREAT | 0644);
		data = shmat(shmd,0 ,0);
		// 2nd argument used for specifying address
		// SHM_RDONLY FLAG as third argument if specified
		if (!(*data)){
			printf("New segment,nothing there\n");
			printf("Add data? (y/n): ");
		}
		else{
			// printf()
			printf("Current content is: %s\n",data);
			printf("Modify data? (y/n): ");
		}
		// printf("More data? (y/n): ");
		char input[3];
		fgets(input,3,stdin);
		if (input[0] == 'y'){
			printf("Enter new data: ");
			fgets(data,200,stdin);
			// *strchr(data,'\0');
			// *strchr(data,'\n') = 0;
			printf("Content is now: %s",data);
			//write to file
			int output = open("story.txt",O_WRONLY|O_CREAT, 0666);
			write(output,data,strlen(data));
		}

	}
}






