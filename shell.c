#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

/** Sean Smith
 *  260787775
 *  U3 Software Eng */  

void displayCode(int errorCode, char *cmd){
    if(errorCode==-1){
        printf("ERRORCODE -1 : Ran out of shell memory.\n");
    }
    if(errorCode==-2){
        printf("ERRORCODE -2 : Incorrect number of inputs for %s. \n", cmd);
    }    
    if(errorCode==-3){
        printf("ERRORCODE -3 : Script not found.\n");
    }    
    if(errorCode==-4){
        printf("ERRORCODE -4 : '%s' Is an unknown command.\n", cmd);
    }    
    if(errorCode==-5){
        printf("ERRORCODE -5 : Working space required for '%s' is too large for RAM.\n", cmd);
    }    
    if(errorCode==-6){
        printf("ERRORCODE -6 : %s command is already loaded.\n", cmd);
    }
}


int parse(char ui[]){
    int w=0;            //words index
    char tmp[1000];     //used to extract word
    char *words[10];    //array of words
    int a,b;            //user interface character index

    for(int i=0; i<10; i++){                                            //Fill up all words
        words[i] = "_NONE_";                                            //With default placeholder value "_NONE_"
    }
    for(a=0; (ui[a]==' ') && (a<1000); a++);                            //skips whitespaces
    
    while( (ui[a]!='\0')  && ui[a] != '\n' &&(a<1000) ){                //parse input until carriage return, and input<1000 characters
        for(b = 0;                                                      //terminate when user enters a space, keep track of indices for chars in words
            ui[a] != '\0'   &&                                          //keep track of indices for chars in words
            ui[a] != '\n'   && 
            ui[a] != '\r'   && 
            ui[a] != ' '    && 
            a < 1000;
            a++, b++){
                tmp[b] = ui[a];                                         //extracts a word, a printf here would be the 'words' without spaces
        }
        tmp[b] = '\0';
        words[w] = strdup(tmp);                                         //duplicate extracted word into words array
        if (ui[a] == '\0' || ui[a] == '\n' || ui[a] == '\r'){
            break;
        }
        for (; ui[a] == ' ' && a < 1000; a++);                          // skip white spaces
        w++;
    }
    return interpreter(words);                                          //different error codes
}


int shellUI(){                                  //  |------User interface------|
    printf("Welcome to the SEAN SMITH shell!\nVersion 3.0 Created March 2020\n");
    char prompt[100] = {'$' , '\0'};            //Potentially change $ in the future.
    char userInput[1000];                       //Users' input stored here
    int errorCode = 0;                          //Define 0 as no error by default.
    while(1){
        printf("%s " , prompt);                 //prints the prompt to screen with a space after the $ prompt
        fgets(userInput, 999, stdin);           //limit input array size to 999 characters to enter
        errorCode = parse(userInput);           //we'll say normal error codes as varying positive integers,

        if(errorCode == 1){                     //User voluntarily quits
            exit(EXIT_SUCCESS);                 //exit(1) means succesful exit        
        }
        else if(errorCode != 0){
            userInput[strlen(userInput) - 1] = '\0';    //Removes trailing carriage returns
            displayCode(errorCode, userInput);
        }
    }
}