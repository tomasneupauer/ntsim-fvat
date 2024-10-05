#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <globals.h>
using namespace std;

class Memory{
    private:
        byte_t *randomAccessMemory;
        size_t memorySize;
        byte_t memoryBank;
        byte_t executionBank;
    
    public:
        Memory(FILE *binfp){
            fseek(binfp, 0, SEEK_END);
            memorySize = ftell(binfp);
            randomAccessMemory = (byte_t*)malloc(memorySize*sizeof(byte_t));
            fseek(binfp, 0, SEEK_SET);
            fread(randomAccessMemory, sizeof(byte_t), memorySize, binfp);
            memoryBank = 0;
            executionBank = 0;
        }

        void onLowStepClock(Control *control){
            
        }

        void dumpMemory(){
            for (int i=0; i<memorySize; i++){
                printf("0x%02X\n", randomAccessMemory[i]);
            }
        }
};

#endif

