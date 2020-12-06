#include<string.h>
#include"ram.h"
#include"interpreter.h"
#include"shell.h"

#define DEFAULT_QUANTA 2

struct CPU { 
    int IP;
    char IR[1000]; 
    int quanta; 
}   CPU;


int runCPU(int quanta){
    if(quanta > DEFAULT_QUANTA){    //can't pass more than the default amount of quanta, otherwise
        quanta = DEFAULT_QUANTA;    //we set it to the default amount
    }
    for(int i=0; i<quanta; i++){
        strcpy(CPU.IR, ram[CPU.IP]);                        //Copy the program line onto the RAM at the instruction pointer index
        int errorCode = parse(CPU.IR);
        if (errorCode != 0){                                //Do error checking and if error, return error
            if (errorCode < 0){
                ram[CPU.IP][strlen(ram[CPU.IP])-2]='\0';
                displayCode(errorCode,ram[CPU.IP]);
            }
            return errorCode;
        }
        CPU.IP ++;                                          //Executes number of lines in RAM for the line of code
    }
    return 0;
}