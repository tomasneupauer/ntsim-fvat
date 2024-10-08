#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstring>
#include "globals.hpp"
#include "control.hpp"
using namespace std;

#define MEMORY_ALIGN 1024

class Memory{
    private:
        byte_t *randomAccessMemory;
        byte_t *videoMemory;
        size_t memorySize;
        size_t videoSize;
        byte_t memoryBank;
        byte_t executionBank;
        long_addr_t lastMemoryAddress;
        long_addr_t lastProgramAddress;

        void reallocateMemory (long_addr_t address){
            if (address >= memorySize){
                size_t oldSize = memorySize;
                memorySize = (address / MEMORY_ALIGN + 1) * MEMORY_ALIGN;
                randomAccessMemory = (byte_t*)realloc(randomAccessMemory, memorySize);
                memset(randomAccessMemory + oldSize, 0, memorySize - oldSize);
            }
        }

    public:
        Memory(FILE *binfp, size_t videoSizePreset){
            fseek(binfp, 0, SEEK_END);
            memorySize = ftell(binfp);
            randomAccessMemory = (byte_t*)malloc(memorySize*sizeof(byte_t));
            fseek(binfp, 0, SEEK_SET);
            fread(randomAccessMemory, sizeof(byte_t), memorySize, binfp);
            videoSize = videoSizePreset;
            videoMemory = (byte_t*)malloc(videoSize*sizeof(byte_t));
            memoryBank = 0;
            executionBank = 0;
            lastMemoryAddress = 0;
            lastProgramAddress = 0;
        }

        byte_t readRandomAccessMemory(long_addr_t address){
            if (address < memorySize){
                return randomAccessMemory[address];
            }
            return 0;
        }

        void onLowStepClock(Control *control){
            if (control->signalValue("RO")){
                long_addr_t address = control->longAddress(memoryBank);
                control->setDataBus(readRandomAccessMemory(address));
                lastMemoryAddress = address;
            }
            if (control->signalValue("MO")){
                long_addr_t address = control->longAddress(executionBank);
                control->setDataBus(readRandomAccessMemory(address));
                lastProgramAddress = address;
            }
            if (control->signalValue("EB")){
                if (control->signalValue("SE")){
                    control->setDataBus(executionBank);
                }
                else {
                    control->setDataBus(memoryBank);
                }
            }
        }

        void onHighStepClock(Control *control){
            if (control->signalValue("RI")){
                long_addr_t address = control->longAddress(memoryBank);
                if (memoryBank & 0x80 && address < videoSize){
                    videoMemory[address] = control->getDataBus();
                }
                else {
                    reallocateMemory(address);
                    randomAccessMemory[address] = control->getDataBus();
                    lastMemoryAddress = address;
                }
            }
            if (control->signalValue("LB")){
                if (control->signalValue("SE")){
                    executionBank = control->getDataBus();
                }
                else {
                    memoryBank = control->getDataBus();
                }
            }
        }

        long_addr_t getLastMemoryAddress(){
            return lastMemoryAddress;
        }

        long_addr_t getLastProgramAddress(){
            return lastProgramAddress;
        }

        byte_t getMemoryBank(){
            return memoryBank;
        }

        byte_t getExecutionBank(){
            return executionBank;
        }

        void dumpMemory(){
            for (int i=0; i<memorySize; i++){
                printf("%02X ", randomAccessMemory[i]);
            }
            cout << endl;
        }
};

#endif

