#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

PCB* makePCB(int start, int end, int totalPages){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;

    pcb->PC_page = 0;
    pcb->PC_offset = 0;


    for(int i=0; i<10; i++){
        pcb->pageTable[i] = -1;
    }

    return pcb;
}

