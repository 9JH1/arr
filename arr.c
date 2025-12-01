#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <stdlib.h> // atoi()
#include <sys/stat.h> // stat() stat
#include <time.h> // time_t
#include <signal.h> // signal()
#include <unistd.h> // sleep()


// Definitions
#define BUFFER_SIZE 256

// Variables
FILE *fptr;


// Function Declaration
void exit_close(int);
time_t gmt(const char *);
void db_impl(int);
void help();


int main(int argc, char *argv[]){
	char*filename="",
			*command="echo \"hello world\"",
			*message="File Edited";

	int interval=1,
			no_message=0,
			no_command=0,
			no_startup=0;
	
	time_t modtime=0;
		
	signal(SIGINT, exit_close);

	// Parse arguments
	if(argc>1){
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
	} else
		help();
	
	// Open file 
	fptr=fopen(filename,"r");

	if(!fptr){
		printf("Error - File Not Found\n");
		exit(1);
	}

	// Start up wait loop
	time_t modtime_current;
	
	if(no_startup)
		modtime = gmt(filename);

	while(1){
		fptr=fopen(filename,"r");
		if(fptr){
			modtime_current = gmt(filename);
			if(modtime_current > modtime){
				if(!no_message) printf("%s\n",message);
				if(!no_command) system(command);
				modtime = modtime_current;
			}
		} else
			printf("Could not open file.\n");
		
		sleep(interval);
	}
	return 0;
}

void exit_close(int c)
{
	printf("CTRL+C pressed, exiting\n");
	fclose(fptr);
	exit(0);
}

time_t gmt(const char *file_path)
{
	struct stat file_stat;
	
	if(stat(file_path,&file_stat) == -1){
		printf("error - Issue with gmt func\n");
		exit(1);
	}

	return file_stat.st_mtime;
}

void help()
{
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
