#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "globals.hpp"
using namespace std;

#define MEMORY_ALIGN 1024

class Memory{
    private:
        byte_t *randomAccessMemory;
        size_t memorySize;
        byte_t memoryBank;
        byte_t executionBank;

        long_addr_t longAddress(addr_t memoryAddress, byte_t bankByte){
            return ((long_addr_t)bankByte & 0x7f) << 16 | memoryAddress;
        }

        void storeWord (byte_t data, long_addr_t address){
            if (address >= memorySize){
                memorySize = (address / MEMORY_ALIGN + 1) * MEMORY_ALIGN;
                randomAccessMemory = (byte_t*)realloc(randomAccessMemory, memorySize);
            }
            randomAccessMemory[address] = data;
        }

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
            if (control->signalValue("RO")){
                long_addr_t address = longAddress(control->getMemoryAddress(), memoryBank);
                if (address < memorySize){
                    control->setDataBus(randomAccessMemory[address]);
                }
                else{
                    control->setDataBus(0);
                }
            }
            if (control->signalValue("MO")){
                long_addr_t address = longAddress(control->getMemoryAddress(), executionBank);
                if (address < memorySize){
                    control->setDataBus(randomAccessMemory[address]);
                }
                else{
                    control->setDataBus(0);
                }
            }
        }

        void onHighStepClock(Control *control){
            if (control->signalValue("RI")){
                long_addr_t address = longAddress(control->getMemoryAddress(), memoryBank);
                if (memoryBank & 0x80){
                    //write VRAM
                }
                else {
                    storeWord(control->getDataBus, address);
                }
            }
        }

        void dumpMemory(){
            for (int i=0; i<memorySize; i++){
                printf("0x%02X\n", randomAccessMemory[i]);
            }
        }
};

#endif

