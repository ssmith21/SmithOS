#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "shellmemory.h"
#include "kernel.h"
#include "pcb.h"
#include "memorymanager.h"


#define TRUE 1
#define FALSE 0

int help() {
    printf("\t\t=========== Available Commands in shell: ===========\n");
    printf("\t\tquit\t\tExits the shell.\n");
    printf("\t\tset VAR STRING\tAssigns a value to the shell memory\n");
    printf("\t\tprint VAR\tDisplays the string assigned to VAR\n");
    printf("\t\trun SCIPT.TXT\tExecutes the file in SCRIPT.txt\n");
    return 0;
}

int quit(){
    printf("\nBye!\n");
    return 1;
}

int set(char *words[]){                             //Set variables in memory:
	char* variable = strdup(words[1]);              //VAR pointer to be stored in shellmemory
	char* value = strdup(words[2]);                 //VAR's value, VAL
    int storedConfirmation = save(variable,value);  //Set by store() in shellmemory,
    return storedConfirmation;                      //0-->succesful, 3-->failed. 
}

int print(char *words[]){                           //given a variable, prints a value
	char *lookupVar = strdup(words[1]);
	char *lookupVal = extract(lookupVar);
	if(!lookupVal){
		printf("Variable does not exist\n");
		return 0;
	}
	printf("%s\n", lookupVal);
	return 0;
}

static int run(char *words[]){
    int runConfirmation=0;
	char* filen = strdup(words[1]);
    char* fileName = strtok(filen, "\n");

    char line[1000];
    FILE *p = fopen(fileName, "r");
    
	if(!p){                             //check to make sure the script exists.
		printf("Script not found\n");
		return runConfirmation;         //return 0 if script doesn't exist.
	}

    fgets(line,999,p);                  //avoid redundant \n causing an unknown command to be run initially
    while( !feof(p) ){                  //continue until end of file.
        runConfirmation = parse(line);  //calls shell
        if(runConfirmation!=0){         //if there's an error in the script, close file and go back to prompt
            fclose(p);
            return runConfirmation;
        }
        fgets(line,999,p);
    }
    fclose(p);
    return runConfirmation;
}

int exec(char *words[]){

    char * filename[3] = { "_NONE_", "_NONE_", "_NONE_"};       //file names to be replaced
    int nextFree = 0;                                           //index of file to be run to replace the "_NONE_" from filename array
    int errorCode = 0;
    for (int i = 1; i <= 3; i++){                               //iterate through arguments passed in exec
        if ( strcmp(words[i],"_NONE_") != 0 ) {                 //if the argument is not empty
            filename[nextFree] = strdup(words[i]);              //replace the "_NONE_" at index "nextfree"
            nextFree++;                                         //index of next "_NONE_" to be replaced
            errorCode = myinit(words[i]);                       //initialize program to be run
            if (errorCode < 0){                                 //check for errors, abort if there is an error
                displayCode(errorCode,words[i]);
                printf("ERROR: aborting exec command...\n");
                emptyReadyQueue();
                return 0;
            }
        } else {                                                //We've ran through every filenames
            break;                                              //so get out of the for loop     
        }
    }

    

    printf("\tSTARTING CONCURRENT PROGRAMS [ ");
    for (int i = 0; i < 3; i++){
        if ( strcmp(filename[i],"_NONE_") != 0 ){
            printf("%s ", filename[i]);
        }
    }
    printf("]\n");
    scheduler();
    return 0;
}


int interpreter(char *words[]){
    int errCode = 0;
	if(strcmp(words[0],"help")==0){                             //help sets error code to 0           strcmp(words[0],strtok("help\n"," "))==0
		errCode = help();
	}	else if (strcmp(words[0],"quit")==0){                   //quit sets error code to 1
		errCode = quit();
	}	else if (strcmp(words[0],"set")==0){                    //set VAR STRING sets error code to 0, or 3 if failed
        errCode = set(words);
	}	else if (strcmp(words[0],"print")==0){                  //print sets error code to 0
		errCode = print(words);
	}	else if (strcmp(words[0], "run")==0){                   //run sets error code to 0
		errCode = run(words);
	}   else if ( strcmp(words[0],"exec") == 0 ) {              // check if there are [2,4] arguments
        if (strcmp(words[1],"_NONE_") == 0  || 
            strcmp(words[4],"_NONE_") != 0 ) {
            return -2;
        }
        errCode = exec(words);
    }   else {
		errCode = -4;
	}
    return errCode;
    
}
