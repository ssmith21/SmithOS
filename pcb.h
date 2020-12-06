typedef struct PCB{ // Process Controll Block
    int PC;         // points to current line of the program, only updated after task switch
    int start;      // points to first line of the program
    int end;        // points to last line of the program

    int pageTable[10];
    int PC_page;
    int PC_offset;
    int pages_max;
}   PCB;

PCB* makePCB(int start, int end, int totalPages);   //Creates a PCB with fields for start and end index of code