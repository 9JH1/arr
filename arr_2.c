/* Automatic
 * Read
 * (and)
 * Runner
 *
 * -- DETAILS -- 
 * Version: 2.2
 * Author : :3hy (@9jh1)
 *
 * -- DESCRIPTION -- 
 * await file change and run command when changed
 *
 * -- ARGUMENTS --
 * interval, interval in seconds when the file is checked for changes
 * command, the command that is run when the file is changed
 * file, the file to watch
 * help, show dialog like this
 *
 * -- REQUIREMENTS --
 * have ctrl+c handling ( using signal )
 * handle all faults and issues unlike the previous versions
 */


#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <stdlib.h> // atoi()
#include <sys/stat.h> // stat() stat
#include <time.h> // time_t
#include <signal.h> // signal()
#include <unistd.h> // sleep()

#define BUFFER_SIZE 256

// global file var
FILE *fptr;

void exit_close(){
	printf("CTRL+C pressed, exiting\n");
	fclose(fptr);
	exit(0);
}

time_t gmt(const char *file_path){
	struct stat file_stat;
	if(stat(file_path,&file_stat) == -1){
		printf("error - Issue with gmt func\n");
		exit(1);
	}
	return file_stat.st_mtime;
}

#define db() db_impl(__LINE__)
void db_impl(int line){
	printf("%d - debug\n",line);
	fflush(stdout);
}

void help(){
	printf("\"Auto Read-Runner\"\n");
	printf("does something when a file is modifyed\n");
	printf("* * * * * * *\n");
	printf("arr [OPTIONS]\n");
	printf("OPTIONS:\n");
	printf("--command    | command run when file is modifyed\n");
	printf("--interval   | interval in seconds the file is checked\n");
	printf("--message    | message showen when file is edited\n");
	printf("--no-message | disable showing message\n");
	printf("--no-command | disable running command\n");
	printf("--no-startup | disable file check on script start\n");
	exit(0);
}

int main(int argc, char *argv[]){
	char*filename="",
			*command="echo \"hello world\"",
			*message="File Edited";
	int interval=1,
			no_message=0,
			no_command=0,
			no_startup=0;
	time_t modtime=0;
		
	signal(SIGINT,exit_close);
	if(argc>1){ // run the arguments
		for(int i=1;i<argc;i++){
			char *argn=argv[i+1];
			if(argn){
				if(strcmp("--file",argv[i])==0) filename=argn;
				else if (strcmp("--command",argv[i])==0) command=argn;
				else if (strcmp("--interval",argv[i])==0) interval = atoi(argn);
				else if (strcmp("--message",argv[i])==0) message = argn;
			} else {
				if (strcmp("--no-message",argv[i])==0) no_message=1;
				else if (strcmp("--no-command",argv[i])==0) no_command=1;
				else if (strcmp("--no-startup",argv[i])==0) no_startup=1;
				else if (strcmp("--help",argv[i])==0) help(); 
			}
		}
	} else {
		help();
	}
	
	fptr=fopen(filename,"r");
	if(!fptr){ // ^ verify file
		printf("Error - File Not Found\n");
		exit(1);
	}

	time_t modtime_current;
	if(no_startup) {
		modtime = gmt(filename);
	}
	while(1){ // infinite loop
		fptr=fopen(filename,"r");
		if(fptr){
			modtime_current = gmt(filename);
			if(modtime_current > modtime){
				if(!no_message) printf("%s\n",message);
				if(!no_command) system(command);
				modtime = modtime_current;
			}
		} else {
			// TODO error checking here
		}
		sleep(interval);

	}
	return 0;
}
