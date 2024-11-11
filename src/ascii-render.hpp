#ifndef ASCII_RENDER_HPP
#define ASCII_RENDER_HPP

#include <bitset>
#include "control.hpp"
#include "bridge.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "globals.hpp"
using namespace std;

#define MEMORY_PADDING 15
#define SYSTEM_PADDING 20
#define BUS_PADDING 14
#define ROW_PADDING 15
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
        return "\e[7m\e[1;32m" + signal + "\e[0m";
    }
    return signal;
}

string toggleFlag(string flag, bool toggled){
    if (toggled){
        return "\e[7m\e[1;31m" + flag + "\e[0m";
    }
    return flag;
}

void formatMemory(Memory *memory){
    padLine(MEMORY_PADDING);
    printf("    Addr              Program            Addr              Memory\n");
    padLine(MEMORY_PADDING);
    printf("|----------|-------------------------|----------|-------------------------|\n");
    long_addr_t lastProgramAddress = memory->getLastProgramAddress();
    long_addr_t lastMemoryAddress = memory->getLastMemoryAddress();
    long_addr_t programIterator = lastProgramAddress / MEMORY_CELLS * MEMORY_CELLS;
    long_addr_t memoryIterator = lastMemoryAddress / MEMORY_CELLS * MEMORY_CELLS;
    for (int row=0; row<MEMORY_ROWS; row++){
        padLine(MEMORY_PADDING);
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
    padLine(MEMORY_PADDING);
    printf("|----------|-------------------------|----------|-------------------------|\n\n");
}

void formatTopSegment(Control *control, System *system, bool clock){
    padLine(SYSTEM_PADDING);
    printf("      Registers                               Controls\n");
    padLine(SYSTEM_PADDING);
    printf("|---------|---------|");
    padLine(BUS_PADDING);
    printf("|----------------|------|----|\n");
    padLine(SYSTEM_PADDING);
    printf("| A  0x%02X | E  0x%02X |", system->getRegister(0), system->getRegister(4));
    padLine(BUS_PADDING);
    int opcode = control->getOpcode();
    string instBin = bitset<8>(opcode).to_string();
    string instName = INSTRUCTIONS[opcode >> 4] + (opcode & 0x08 ? "I" : "R");
    printf("| IR  0b%s | %s | %s |\n", instBin.c_str(), instName.c_str(), toggle(control, "LI").c_str());
    padLine(SYSTEM_PADDING);
    printf("| B  0x%02X | F  0x%02X |", system->getRegister(1), system->getRegister(5));
    padLine(BUS_PADDING);
    printf("|----------------|------|----|\n");
    padLine(SYSTEM_PADDING);
    printf("| C  0x%02X | G  0x%02X |", system->getRegister(2), system->getRegister(6));
    //padLine(BUS_PADDING);
    printf("---------+----");
    printf("| MAR 0x%04X            | %s |\n", control->getMemoryAddressRegister(), toggle(control, "LM").c_str());
    padLine(SYSTEM_PADDING);
    printf("| D  0x%02X | H  0x%02X |", system->getRegister(3), system->getRegister(7));
    //padLine(BUS_PADDING);
    printf("         |    ");
    printf("|-----------------------|----|\n");
    padLine(SYSTEM_PADDING);
    printf("|---------|---------|");
    //padLine(BUS_PADDING);
    printf("----+----(----");
    string stepBin = bitset<4>(control->getStepCounter()).to_string();
    printf("| SC  0b%s            | %s |\n", stepBin.c_str(), toggle(control, "XT").c_str());
    padLine(SYSTEM_PADDING);
    printf("| %s    %s    %s    |", toggle(control, "LR").c_str(), toggle(control, "ER").c_str(), toggle(control, "LF").c_str());
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|-----------------------|----|\n");
    padLine(SYSTEM_PADDING);
    printf("|    %s    %s    %s |", toggle(control, "AR").c_str(), toggle(control, "LG").c_str(), toggle(control, "LH").c_str());
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    int interruptFlags = control->getInterruptFlags();
    string hltFlag = toggleFlag("HLT", interruptFlags & 0x01);
    string intFlag = toggleFlag("INT", interruptFlags & 0x02);
    string cofFlag = toggleFlag("COF", interruptFlags & 0x04);
    string sofFlag = toggleFlag("SOF", interruptFlags & 0x08);
    string clockFlag = toggleFlag("MC", clock);
    printf("| %s   %s   %s   %s | %s |\n", hltFlag.c_str(), intFlag.c_str(), cofFlag.c_str(), sofFlag.c_str(), clockFlag.c_str());
    padLine(SYSTEM_PADDING);
    printf("|-------------------|");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|-----------------------|----|\n");
    padLine(SYSTEM_PADDING + 21);
    printf("    |    |    \n");
}

void formatMiddleSegment(Control *control, System *system){
    byte_t opcode = control->getOpcode();
    byte_t data = control->getDataBus();
    padLine(SYSTEM_PADDING);
    printf("       A-L Unit      ");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("            Buses\n");
    padLine(SYSTEM_PADDING);
    printf("|---------|---------|");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|----------------------------|\n");
    padLine(SYSTEM_PADDING);
    printf("| X  0x%02X |   i %d   |", system->getRegisterX(), system->getCarryIn());
    //padLine(BUS_PADDING);
    printf("    |    +----");
    printf("| ADDRESS   0x%04X           |\n", control->getAddressBus());
    padLine(SYSTEM_PADDING);
    printf("| Y  0x%02X |   o %d   |", system->getRegisterY(), system->getCarryOut(opcode));
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("| OP CODE   0b%s  0x%02X |\n", bitset<8>(opcode).to_string().c_str(), opcode);
    padLine(SYSTEM_PADDING);
    string instrName = (opcode >> 4 > 8 ? INSTRUCTIONS[opcode >> 4] : "XXX");
    printf("| Z  0x%02X |   %s   |", system->getRegisterZ(opcode), instrName.c_str());
    //padLine(BUS_PADDING);
    printf("----+----(----");
    printf("| DATA      0b%s  0x%02X |\n", bitset<8>(data).to_string().c_str(), data);
    padLine(SYSTEM_PADDING);
    printf("|---------|---------|");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|----------------------------|\n");
    padLine(SYSTEM_PADDING);
    printf("| %s   %s   ", toggle(control, "LX").c_str(), toggle(control, "LY").c_str());
    printf("%s   %s |", toggle(control, "EZ").c_str(), toggle(control, "EF").c_str());
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|   %s  %s  %s  ", toggle(control, "RI").c_str(), toggle(control, "RO").c_str(), toggle(control, "MO").c_str());
    printf("%s  %s  %s   |\n", toggle(control, "PI").c_str(), toggle(control, "PO").c_str(), toggle(control, "SE").c_str());
    padLine(SYSTEM_PADDING);
    printf("|-------------------|");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|----------------------------|\n");
    padLine(SYSTEM_PADDING + 21);
    //padLine(BUS_PADDING);
    printf("    |    |    \n");
}

void formatBottomSegment(Control *control, Bridge *bridge, System *system, Memory *memory){
    padLine(SYSTEM_PADDING);
    printf("        Banks        ");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("           Pointers\n");
    padLine(SYSTEM_PADDING);
    printf("|----------|--------|");
    //padLine(BUS_PADDING);
    printf("    |    |    ");
    printf("|-----------|----------------|\n");
    padLine(SYSTEM_PADDING);
    printf("| MB  0x%02X |   %s   |", memory->getMemoryBank(), toggle(control, "LB").c_str());
    //padLine(BUS_PADDING);
    printf("    |    +----");
    printf("| PC 0x%04X | %s %s", system->getProgramCounter(), toggle(control, "IC").c_str(), toggle(control, "RC").c_str());
    printf(" %s %s %s |\n", toggle(control, "LC").c_str(), toggle(control, "EC").c_str(), toggle(control, "AC").c_str());
    padLine(SYSTEM_PADDING);
    printf("| EB  0x%02X |   %s   |", memory->getExecutionBank(), toggle(control, "EB").c_str());
    //padLine(BUS_PADDING);
    printf("    |         ");
    printf("|-----------|----------------|\n");
    padLine(SYSTEM_PADDING);
    printf("| PR  0x%02X |   %s   |", bridge->getPortRegister(), toggle(control, "LP").c_str());
    //padLine(BUS_PADDING);
    printf("----+---------");
    printf("| SP 0x%04X | %s %s", system->getStackPointer(), toggle(control, "IS").c_str(), toggle(control, "DS").c_str());
    printf(" %s %s %s |\n", toggle(control, "LS").c_str(), toggle(control, "ES").c_str(), toggle(control, "AS").c_str());
    padLine(SYSTEM_PADDING);
    printf("|----------|--------|");
    padLine(BUS_PADDING);
    printf("|-----------|----------------|\n\n");
}

void updateAsciiRender(Control *control, Bridge *bridge, System *system, Memory *memory, bool clock){
    printf("\e[2J\e[H\n");
    formatMemory(memory);
    formatTopSegment(control, system, clock);
    formatMiddleSegment(control, system);
    formatBottomSegment(control, bridge, system, memory);
}

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

#endif

