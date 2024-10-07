#ifndef ASCII_RENDER_HPP
#define ASCII_RENDER_HPP

#include <bitset>
#include "control.hpp"
#include "bridge.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "globals.hpp"
using namespace std;

#define ROW_PADDING 5
#define BUS_PADDING 14
#define MEMORY_ROWS 8
#define MEMORY_COLS 8
#define MEMORY_CELLS (MEMORY_ROWS * MEMORY_COLS)

void padLine(int padding){
    if (padding){
        cout << string(padding, ' ');
    }
}

string toggle(Control *control, string signal){
    if (control->signalValue(signal)){
        return "\e[1;32m" + signal + "\e[0m";
    }
    return signal;
}

string toggleFlag(string flag, bool toggled){
    if (toggled){
        return "\e[1;31m" + flag + "\e[0m";
    }
    return flag;
}

void formatMemory(Control *control, Memory *memory){
    padLine(ROW_PADDING);
    printf("    Addr              Program            Addr              Memory\n");
    padLine(ROW_PADDING);
    printf("|----------|-------------------------|----------|-------------------------|\n");
    long_addr_t lastProgramAddress = memory->getLastProgramAddress();
    long_addr_t lastMemoryAddress = memory->getLastMemoryAddress();
    long_addr_t programIterator = lastProgramAddress / MEMORY_CELLS * MEMORY_CELLS;
    long_addr_t memoryIterator = lastMemoryAddress / MEMORY_CELLS * MEMORY_CELLS;
    for (int row=0; row<MEMORY_ROWS; row++){
        padLine(ROW_PADDING);
        printf("| 0x%06X | ", programIterator);
        for (int col=0; col<MEMORY_COLS; col++){
            byte_t data = memory->readRandomAccessMemory(programIterator);
            if (programIterator == lastProgramAddress){
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
            if (memoryIterator == lastMemoryAddress){
                printf("\e[7m%02X\e[0m ", data);
            }
            else {
                printf("%02X ", data);
            }
            memoryIterator++;
        }
        printf("|\n");
    }
    padLine(ROW_PADDING);
    printf("|----------|-------------------------|----------|-------------------------|\n");
}

void formatTopSegment(Control *control, System *system, bool clock){
    padLine(2*ROW_PADDING);
    printf("      Registers                               Controls\n");
    padLine(2*ROW_PADDING);
    printf("|---------|---------|");
    padLine(BUS_PADDING);
    printf("|----------------|------|----|\n");
    padLine(2*ROW_PADDING);
    printf("| A  0x%02X | E  0x%02X |", system->getRegister(0), system->getRegister(4));
    padLine(BUS_PADDING);
    int opcode = control->getOpcode();
    string instBin = bitset<8>(opcode).to_string();
    string instName = INSTRUCTIONS[opcode >> 4] + (opcode & 0x08 ? "I" : "R");
    printf("| IR  0b%s | %s | %s |\n", instBin.c_str(), instName.c_str(), toggle(control, "LI").c_str());
    padLine(2*ROW_PADDING);
    printf("| B  0x%02X | F  0x%02X |", system->getRegister(1), system->getRegister(5));
    padLine(BUS_PADDING);
    printf("|----------------|------|----|\n");
    padLine(2*ROW_PADDING);
    printf("| C  0x%02X | G  0x%02X |", system->getRegister(2), system->getRegister(6));
    padLine(BUS_PADDING);
    printf("| MAR 0x%04X            | %s |\n", control->getMemoryAddressRegister(), toggle(control, "LM").c_str());
    padLine(2*ROW_PADDING);
    printf("| D  0x%02X | H  0x%02X |", system->getRegister(3), system->getRegister(7));
    padLine(BUS_PADDING);
    printf("|-----------------------|----|\n");
    padLine(2*ROW_PADDING);
    printf("|---------|---------|");
    padLine(BUS_PADDING);
    string stepBin = bitset<4>(control->getStepCounter()).to_string();
    printf("| SC  0b%s            | %s |\n", stepBin.c_str(), toggle(control, "XT").c_str());
    padLine(2*ROW_PADDING);
    printf("| %s    %s    %s    |", toggle(control, "LR").c_str(), toggle(control, "ER").c_str(), toggle(control, "LF").c_str());
    padLine(BUS_PADDING);
    printf("|-----------------------|----|\n");
    padLine(2*ROW_PADDING);
    printf("|    %s    %s    %s |", toggle(control, "AR").c_str(), toggle(control, "LG").c_str(), toggle(control, "LH").c_str());
    padLine(BUS_PADDING);
    int interruptFlags = control->getInterruptFlags();
    string hltFlag = toggleFlag("HLT", interruptFlags & 0x01);
    string intFlag = toggleFlag("INT", interruptFlags & 0x02);
    string cofFlag = toggleFlag("COF", interruptFlags & 0x04);
    string sofFlag = toggleFlag("SOF", interruptFlags & 0x08);
    string clockFlag = toggleFlag("MC", clock);
    printf("| %s   %s   %s   %s | %s |\n", hltFlag.c_str(), intFlag.c_str(), cofFlag.c_str(), sofFlag.c_str(), clockFlag.c_str());
    padLine(2*ROW_PADDING);
    printf("|-------------------|");
    padLine(BUS_PADDING);
    printf("|-----------------------|----|\n");
}

void updateAsciiRender(Control *control, Bridge *bridge, System *system, Memory *memory, bool clock){
    printf("\e[2J\e[H\n");
    formatMemory(control, memory);
    printf("\n\n");
    formatTopSegment(control, system, clock);
    printf("\n\n");
}

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

#endif

