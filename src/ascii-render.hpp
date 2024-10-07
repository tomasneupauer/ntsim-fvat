#ifndef ASCII_RENDER_HPP
#define ASCII_RENDER_HPP

#include "control.hpp"
#include "bridge.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "globals.hpp"
using namespace std;

#define PADDING 0
#define MEMORY_ROWS 8
#define MEMORY_COLS 4
#define MEMORY_CELLS MEMORY_ROWS * MEMORY_COLS

void padLine(){
    if (PADDING){
        cout << string(PADDING, ' ');
    }
}

void formatMemory(Control *control, Memory *memory){
    padLine();
    printf("    Addr              Program            Addr              Memory\n");
    padLine();
    printf("|----------|-------------------------|----------|-------------------------|\n");
    long_addr_t currentProgramAddress = control->longAddress(memory->getExecutionBank());
    long_addr_t currentMemoryAddress = control->longAddress(memory->getMemoryBank());
    long_addr_t programIterator = currentProgramAddress / MEMORY_CELLS * MEMORY_CELLS;
    long_addr_t memoryIterator = currentMemoryAddress / MEMORY_CELLS * MEMORY_CELLS;
    for (int row=0; row<MEMORY_ROWS; row++){
        padLine();
        printf("| 0x%06X | ", programIterator);
        for (int col=0; col<MEMORY_COLS; col++){
            byte_t data = memory->readRandomAccessMemory(programIterator);
            if (programIterator == currentProgramAddress){
                printf("\e[7m%02X\e[0m ", data);
            }
            else {
                printf("%02X ", data);
            }
            programIterator++;
        }
        printf("| 0x%06X | ", memoryIterator);
        for (int col=0; col<MEMORY_COLS; col++){
            byte_t data = memory->readRandomAccessMemory(memoryIterator);
            if (memoryIterator == currentMemoryAddress){
                printf("\e[7m%02X\e[0m ", data);
            }
            else {
                printf("%02X ", data);
            }
            memoryIterator++;
        }
        printf("|\n");
    }
    printf("     |----------|-------------------------|----------|-------------------------|\n");
}

void updateAsciiRender(Control *control, Bridge *bridge, System *system, Memory *memory){
    printf("\e[2J\e[H\n");
    formatMemory(control, memory);
}

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

#endif

