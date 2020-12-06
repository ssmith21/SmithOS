#include<stdio.h>
char* ram[1000];                        //Room for 1000 lines of code, at most 3 programs
void removeFromRam (int, int);          //Removes lines of code from RAM in the interval [start,end]
void resetRam();                        //free the cell block back to 0 for each index of the RAM array
void addToRAM (FILE *, int *, int *);   //Adds file to ram. If there's an error, -1 assigned to start and end values.
    //start : points to index of first line of program in RAM (where the program will go)
    //end   : points to index of last line of program in RAM (where the program will go)
