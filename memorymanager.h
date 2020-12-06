#include <stdio.h>
// #include "kernel.h"
// #include "pcb.h"

int launcher(FILE *p);  //only associated with exec, not run. Returns a 1 on succesful program launch.
int countTotalPages(FILE *f);
void loadPage(int pageNumber, FILE *f, int frameNumber);
int findFrame();
int findVictim (PCB *p);
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);
int launcher(FILE *p);