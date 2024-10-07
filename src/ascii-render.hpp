#ifndef ASCII-RENDER_HPP
#define ASCII-RENDER_HPP

#include <vector>
#include <string>
#include "control.hpp"
#include "bridge.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "globals.hpp"
using namespace std;

#define MEMORY_ROWS 8
#define MEMORY_COLS 8

vector<string> staticLines = {
    "\e[2J",
    "         Addr              Program            Addr              Memory",
    "     |----------|-------------------------|----------|-------------------------|",
};

void formatMemory(Control *control, Memory *memory){
    int memoryCells = MEMORY_ROWS * MEMORY_COLS;
    long_addr_t currentProgramAddress = control->longAddress(memory->getExecutionBank());
    long_addr_t currentMemoryAddress = control->longAddress(memory->getMemoryBank());
    long_addr_t programIterator = currentProgramAddress / memoryCells * memoryCells;
    long_addr_t memoryIterator = currentMemoryAddress / memoryCells * memoryCells;
    for (int row=0; row<MEMORY_ROWS; row++){
        printf("     | 0x%06X | ", programIterator);
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
}

void updateAsciiRender(Control *control, Bridge *bridge, System *system, Memory *memory){
    for (int i=0; i<3; i++){
        cout << staticLines[i] << endl;
    }
    formatMemory(control, memory);
}

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

#endif

