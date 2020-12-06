// #include "pcb.h"

int getQueueSize();
struct PCB* dequeue();
void addToReady(struct PCB*);
int myinit(char*);
int scheduler();
void emptyReadyQueue();