#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"shell.h"
#include"pcb.h"
#include"ram.h"
#include"cpu.h"
#include"interpreter.h"
#include"memorymanager.h"

typedef struct ReadyQueueNode {     //Ready Queue implemented as a linked list
    PCB*  PCB;                      //Each node is a PCB pointer
    struct ReadyQueueNode* next;    //And a pointer to the next node
}   ReadyQueueNode;
ReadyQueueNode* head = NULL;        //First PCB in the list (first in)
ReadyQueueNode* tail = NULL;        //Last PCB in the list (last in)
int sizeOfQueue = 0;

void boot(){                        //assumes ram is a global array of size 40 (strings)
    removeFromRam(0,40);            //function form ram.c which sets the values in the inverval to NULL
    system("rm -rf Backingstore && mkdir Backingstore");
    // system("mkdir backingstore");
}

int main(int argc, char const *argv[]){
    int error=0;
    boot();
    //error = kernel();
    //return error;
    shellUI();
}


int getQueueSize(){
    return sizeOfQueue;
}


void addToReady(struct PCB* pcb) {  //Adds a pcb to the tail of the ready queue
    ReadyQueueNode* newNodeToAdd = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNodeToAdd->PCB = pcb;
    newNodeToAdd->next = NULL;
    if(head==NULL){                 //If this ready Queue is empty
        head = newNodeToAdd;
        tail = newNodeToAdd;
    }else{                          //Otherwise the ready queue is not empty
        tail->next = newNodeToAdd;
        tail = newNodeToAdd;
    }
    sizeOfQueue++;                  //Update the size of the ready queue
}


struct PCB* dequeue(){                  //Removes the head of the ready queue
    PCB* nodeToRemove = head->PCB;      //causes an error if queue is empty --> double check that the queue is not empty
    ReadyQueueNode *temp = head;        //using getQueueSize()
    if(head == tail){
        head = NULL;
        tail = NULL;
    }else{
        head = head->next;
    }
    free(temp);
    sizeOfQueue--;
    return nodeToRemove;
}


int myinit(char* filename){
    FILE * filePointer = fopen(filename,"r");           //opens a script called filename
    if (filePointer == NULL) {                          //verify the script exists
        return -3;
    }else{
        int start;
        int end;        
        int totalPages = countTotalPages(filePointer);
        addToRAM(filePointer, &start, &end);            //add the script to RAM if it exists
        if (start == -1){                               //if RAM is full, exit
            return -5;
        }else{
            PCB* pcb = makePCB(start,end,totalPages);   //if the file is not too big, add it to the ready queue
            addToReady(pcb);
            fclose(filePointer);                        //close the file since no longer needed
            return 0;
        }
    }
}


int scheduler(){
    CPU.quanta = DEFAULT_QUANTA;                            //set CPU quanta to default, IP to -1, IR = NULL
    CPU.IP = -1;
    while (getQueueSize() != 0){                            //while there are programs in the ready queue 
        PCB* pcb = dequeue();                               //dequeue the head
        CPU.IP = pcb->PC;                                   //copy program counter of PCB to instruction pointer of CPU

        int isOver = FALSE;                                 //flag to see if the program has finished running
        int remaining = (pcb->end) - (pcb->PC) + 1;         //remaining quanta to be run until program is over
        int quanta = DEFAULT_QUANTA;

        if (DEFAULT_QUANTA >= remaining) {                  //if the initial number of quanta is greater than the remaining
            isOver = TRUE;                                  //then the program is finished
            quanta = remaining;                             //how many qunata are left to be used
        }

        int errorCode = runCPU(quanta);

        if ( errorCode!=0 || isOver ){                      //if the program is over (or the program must stop the kernel)
            removeFromRam(pcb->start,pcb->end);             //remove the program from ram (using the start,end indices of the pcb)
            free(pcb);                                      //free up the pcb
        } else {
            pcb->PC += DEFAULT_QUANTA;                      //otherwise continue
            addToReady(pcb);
        }
    }
    resetRam();
    return 0;
}


//Flushes every pcb off the ready queue in the case of a load error
void emptyReadyQueue(){
    while (head!=NULL){
        ReadyQueueNode * temp = head;
        head = head->next;
        free(temp->PCB);
        free(temp);
    }
    sizeOfQueue =0;
}
