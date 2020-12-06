#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"

// #include "kernel.h"
#include "ram.h"

int countTotalPages(FILE *f){               //returns the total number of pages needed by the program
    int lines = 1;                          //for example, if the program has 4 lines or less, returns 1.
    int c;                                  //if greater [5,8] lines of code, returns 2, etc...  
    int last = '\n';                        //ignore trailing carriage returns in files
    while (EOF != (c = fgetc(f))) {
        if (c == '\n' && last != '\n') {
            ++lines;                        //count number of lines in the file
        }   last = c;
    }
    rewind(f);                              //Reset the file pointer to the start of the file
    if(lines%4==0){
        return (lines/4);                   //multiple of 4 -> can just return the number of lines/4
    }else{
        return ((lines/4)+1);               //not multiple of 4-> make room for remainder lines to put in the pages
    }
}

//FILE *f points to the beginning of the file in the backing store
//pageNumber is the desired page from the backing store
//function loads the 4 lines of code from the page into the frame in ram[]
void loadPage(int pageNumber, FILE *f, int frameNumber){

}


//using FIFO, search ram[] for a frame not equal to NULL.
//If oe exists, then reutn its index number, otherwise return -1
int findFrame(){
    return 20;
}


//only invoked when findFrame() returns -1
//use a random number generator to pick a random frame number.
//if the frame number does not belong to the pages of the active PCB,
//  then return that frame number as victim
//otherwise
//  iteratively incremenet (modulo wise) until you come to a fram number that doesn't belong to the PCB's pages, return that number
int findVictim (PCB *p){

}


//page tables must be updated to reflect the changes
//if a victim was selected, then the PCB page table of the victim must be updated
//we do this once for the PCB asking for the page fault.
//maybe do this again for the victim PCB
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame){

}



// 1) copies entire file into backing store
// 2) close the file pointer pointing to origional file
// 3) open the file in the backing store
// 4) paging technique defaults to loading 2 pages of the program into RAM when 1st launched.
//      page = 4 lines of code
//      if program has 4 lines of code or less
//          only 1 page is loaded
//      if program has more than 8 lines of code
//          then only 1st 2 pages are loaded

extern int launcher(char* filename){
    printf("LAUNCHER --> %s", filename);
}

// int launcher(FILE *p){

// }