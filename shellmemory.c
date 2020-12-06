#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct MEM{
    char *var;
    char *value;
};
struct MEM storage[1000];

int save(char *VAR, char* VAL){                     //store varible and its' associated value in memory
    for(int i=0; i<1000; i++){                      //when storing, incrementally checks next storage[i] to see if something is stored
        if(storage[i].var==NULL){                   //memory free, variable deosn't already exist, store here
            storage[i].var = strdup(VAR);
            storage[i].value = strdup(VAL);
            return 0;                               //0 indicates success
        }else if(!(strcmp(storage[i].var, VAR))){   //variable already exists at storage[i], overwrite its' value
            storage[i].value = strdup(VAL);
            return 0;
        }
    }
}

char* extract(char *VAR){
    char* result = NULL;
    for(int i=0; i<1000; i++){
        if(storage[i].var != NULL){
            
            char* tempVar = strdup(storage[i].var);         //string duplicate of variable in storage
            strtok(tempVar, "\n");                          //remove the carriage return on all strings for easier comparison
            char* tempVal = strdup(storage[i].value);
            strtok(tempVal, "\n");
            char* tempInput = strdup(VAR);
            strtok(tempInput, "\n");

            if(!(strcmp(tempVar,tempInput))){               //if the strings are the same (without the carriage return)
                result = strdup(tempVal);                   //return the value in memory paired with the variable
            }
        }
    }
    return result;                                          //returns NULL if nothing was found.
}

