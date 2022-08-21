#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int i = 0;

void decrease(int a) {
	i = i - 1;
}	

int main(int argc, char* argv[]) {
	
	if(argc != 2){
		printf("Неверное количество параметров командной строки.\n");
		return 1;
	}
	
	

	int N = atoi(argv[1]);
	
	if(N <  0) {
		printf("Неверный параметр командной строки.\n");
		return 2;
	}
	
	char* command;
	command = (char*)malloc(10 * sizeof(char));
	pid_t pid, pid_m[N + 1];
	
	while(1) {
		scanf("%s", command);
		if(strcmp(command, "-1") == 0)
			break;
		if(i < N) {
			signal(SIGCHLD, decrease);	
			pid = fork();
			
			if(pid == -1) {
				printf("Невозможно создать процесс.\n");
				return 3;
			}

			if(pid == 0) {
				pid_m[i] = getpid();
				return system(command);
				
			}
			i = i + 1;
		} else {
			printf("Выполняется %d процессов\n", N);
			}
	}
	for(int j = 0; j < N; j++) 
		kill(pid_m[j], SIGKILL);

	free(command);
	
	return 0;
					
}
