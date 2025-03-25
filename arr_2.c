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
#include <time.h>

// global file var
FILE *fptr;

void close(){
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


int main(int argc, char *argv[]){
	char*filename="",
			*command="",
			*message="File Edited";
	int interval=100;
	time_t modtime=0;

	if(argc>1){ // run the arguments
		for(int i=0;i<argc;i++){
			if(strcmp("--file",argv[i+1])==0) filename=argv[i+2];
			else if (strcmp("--command",argv[i+1])==0) command=argv[i+2];
			else if (strcmp("--interval",argv[i+1])==0) interval = atoi(argv[i+2]);
			else if (strcmp("--message",argv[i+1])==0) message = argv[i+2]; 
		}
	} else {
		// TODO help menu here
	}

	printf("%s\n",command);
	printf("%d\n",interval);
	
	fptr=fopen(filename,"r");
	if(!fptr){ // ^ verify file
		printf("Error - File Not Found\n");
		exit(1);
	}

	while(1){ // infinite loop
		fptr=fopen(filename,"r");
		if(fptr){
			time_t modtime_current = gmt(filename);
			if(modtime_current > modtime){
				printf("%s\n",message);
				// TODO run command here
				modtime = modtime_current;
			}
		} else {
			// TODO error checking here
		}

	}
	return 0;
}
