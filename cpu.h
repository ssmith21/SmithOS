#define DEFAULT_QUANTA 2
struct CPU { 
    int IP;         //Instruction pointer, points to next instruction in RAM
    char IR[1000];  //Instruction register, this is the currently executing instruction
    int quanta;     //Quanta will decrease until 0
}   CPU;
int runCPU(int);
