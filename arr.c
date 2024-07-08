#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


#define IS_TRUE_LITERAL    0
#define NULL_LITERAL_SPACE NULL
#define MAX_OUTPUT_SIZE 2048


//set all of our vars

int timeout =       1;

time_t modtime=     0,     // modification time
       modtimecur=  0;     // modification time current

FILE *file=         NULL,
     *filecommand=  NULL;

char *filepth=      NULL,  // file path
     *command=      NULL,
     *message=      NULL,
     buffer[MAX_OUTPUT_SIZE];


// get the last time the file was modifyed
time_t get_modification_time(const char *file_path) {
    struct stat file_stat;
    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    return file_stat.st_mtime;
}


// main loop takes in arguments 
int main(int argc, char* argv[]){

	// go through each of the arguments
	for(int i=0;i<argc;i++){

		char *localArg = argv[i],
		     *localArgNext = argv[i+1];

		if(strcmp(argv[i],"--help")==IS_TRUE_LITERAL || strcmp(argv[i],"-h")==IS_TRUE_LITERAL  || argc == 1){
			printf("USAGE\narr -f <file> -c <command>\n\nOPTIONS\n  -f <file> file to be listened\n  -c <command> sets the command to run if the file is changed\n  -m <message> sets a message to print on file change\n  -t <timeout> set the interval at which the file is checked\n");
			exit(1);

		} else if (strcmp(localArg,"-f")==IS_TRUE_LITERAL){
			filepth = localArgNext;

		} else if (strcmp(localArg,"-c")==IS_TRUE_LITERAL){
			command = localArgNext;

		} else if (strcmp(localArg,"-m")==IS_TRUE_LITERAL){
			message = localArgNext;

		} else if (strcmp(localArg,"-t")==IS_TRUE_LITERAL){
			timeout = atoi(localArgNext);
		}	
	}

	// make sure that both the file and command vars are valid
        if(filepth == NULL_LITERAL_SPACE || command == NULL_LITERAL_SPACE ){
       		printf("Not enought options specifyed\nrun arr --help for more information\n");
		exit(1);
	}

	//check to see if file exits
	file = fopen(filepth,"r");
	if(file==NULL_LITERAL_SPACE){
		printf("File '%s' not found\n",filepth);
		fclose(file);
		exit(1);
	}

	//check to see if the command exists
	filecommand = popen(command,"r");
	if(filecommand == NULL_LITERAL_SPACE){
		printf("Command '%s' could not be executed\n,",command);
		exit(1);
	}

	// start main loop
	while(1){

		//check to see if the file still exists
		file = fopen(filepth,"r");
		if(file==NULL_LITERAL_SPACE){	
			fclose(file);
			printf("File '%s' not found",filepth);
		}
		
		//get the new mod date
		time_t modtimecur = get_modification_time(filepth);

		// if the modtimecur is larger than modtime 
		// then the file has been modifyed
		if(modtimecur > modtime){

			// if the message var exists then print it
			if(message != NULL_LITERAL_SPACE){
				printf("%s\n",message);
			}

			// run and capture the command
			filecommand = popen(command,"r");
			while(fgets(buffer,sizeof(buffer),filecommand)!=NULL_LITERAL_SPACE){
				printf("%s",buffer);
			}

			// close the popen and reset the modtime counter
			pclose(filecommand);
			modtime = modtimecur;
		}

		//sleep for a specifyed anount of time 
		//seen in timout var
		sleep(timeout);
	}
	return 0;
}
