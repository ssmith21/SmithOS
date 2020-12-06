#include<stdio.h>
#include<string.h>

int nextFreeIndexRAM = 0;   //index of the next available cell in RAM
char *ram[1000];

void removeFromRam(int start, int end){
    for(int i=start; i<end; i++){
        ram[i] = NULL;
    }
}

void resetRam(){
    nextFreeIndexRAM = 0;
}

void addToRAM (FILE *p, int *start, int *end){      //*p file pointer
    *start = nextFreeIndexRAM;                      //line 0 for the program to be added
    int countSuccessiveLines = *start;              //this index will start at line 0, and increase by 1 at every new line of code read in *p
    char buffer[1000];                              //to read the lines of code

    while(!feof(p) && countSuccessiveLines < 1000){ //while we haven't read the entire program and it's not >1000 lines of code
        fgets(buffer,999,p);
        ram[countSuccessiveLines] = strdup(buffer); //copy the fgets into the ram for each line of code
        countSuccessiveLines++;                     //move onto the next line of code
    }

    if(!feof(p) && countSuccessiveLines>1000){                          //If RAM is full and we've not yet reached the end of the code
        removeFromRam(0, countSuccessiveLines-1);                       //clear the RAM
        nextFreeIndexRAM = 0;                                           //reset all indices
        *start = -1;
        *end = -1;
    }else{                                                              //otherwise
        nextFreeIndexRAM = countSuccessiveLines;                        //add the lines of code to ram
        *end = countSuccessiveLines - 1;                                //keep track of where the code ends
    }

}