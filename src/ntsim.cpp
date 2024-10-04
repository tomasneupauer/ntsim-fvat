#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "instructions.hpp"
using namespace std;

typedef unsigned char byte_t;
typedef unsigned short int addr_t;
typedef bool signal_t;
typedef int bus_t;

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

class Control{
    private:
        vector<signal_t> signals;       
        addr_t mem_addr; // Memory Address Register
        bus_t data_bus;
        bus_t addr_bus;
        byte_t opcode; // Instruction Register
        byte_t step; // Step Counter
        int interrupt;
        int state;

        void resetBuses(){
            data_bus = -1;
            addr_bus = -1;
        }

        void updateState(){
            state = opcode & 0xf8 | step & 0x07;
            for (int i=0; i<signals.size(); i++){
                signals[i] = find(MICROCODE[i].begin(), MICROCODE[i].end(), state) != MICROCODE[i].end();
            }
        }

    public:
        Control():
            signals(SIGNALS.size(), 0)
        {
            resetBuses();
            mem_addr = 0;
            opcode = 0;
            step = -1;
            interrupt = 0;
            state = 0;
        }

        signal_t signalValue(string name){
            int index = find(SIGNALS.begin(), SIGNALS.end(), name) - SIGNALS.begin();
            if (index < signals.size()){
                return signals[index];
            }
            return 0;
        }

        void setInterrupt(string flag){
            int index = find(INTERRUPTS.begin(), INTERRUPTS.end(), flag) - INTERRUPTS.begin();
            if (index < INTERRUPTS.size()){
                interrupt |= 1 << index;
            }
        }

        void onLowStepClock(){
            if (!signalValue("XT")){
                step++;
            }
            else {
                step = 0;
            }
            resetBuses();
            updateState();
        }

        int branchSignals(){
            if (data_bus != 0){
                if (state == 114 || state == 123){
                    signals[signalValue("AR")] = 1;
                    signals[signalValue("RC")] = 1;
                    return 1;
                }
                else if (state == 130 || state == 139){
                    setInterrupt("HLT");
                    return 1;
                }
            }
            else if (state == 123 || state == 139){
                signals[signalValue("IC")] = 1;
                return 1;
            }
            return 0;
        }

        int getInterrupt(){
            return interrupt;
        }

        int getStep(){
            return step;
        }
};

class Memory{
    private:
        byte_t *mem_block; // Random Access Memory
        size_t mem_size;
        byte_t mem_bank; // Memory Bank Register
        byte_t exc_bank; // Execution Bank Register
    
    public:
        Memory(FILE *ebf_fp){
            fseek(ebf_fp, 0, SEEK_END);
            mem_size = ftell(ebf_fp);
            mem_block = (byte_t*)malloc(mem_size*sizeof(byte_t));
            fseek(ebf_fp, 0, SEEK_SET);
            fread(mem_block, sizeof(*mem_block), mem_size, ebf_fp);
            mem_bank = 0;
            exc_bank = 0;
        }

        void onLowStepClock(Control *control){
            
        }

        void dumpMemory(){
            for (int i=0; i<mem_size; i++){
                printf("0x%02X\n", mem_block[i]);
            }
        }
};

class System{
    private:
        vector<byte_t> gp_regs; // General Purpose Registers
        vector<byte_t> xy_regs; // Arithmetic Logic Unit Registers
        addr_t program_counter; // Program Counter
        addr_t stack_pointer; // Stack Pointer

    public:
        System():
            gp_regs(8, 0),
            xy_regs(8, 0)
        {
            program_counter = 0;
            stack_pointer = 0;
        }

        void onLowStepClock(Control *control){
        
        }
};

class StepEmulator{
    private:
        Memory memory;
        System system;
        Control control;
        bool clock;

    public:
        StepEmulator(FILE *ebf_fp):
            memory(ebf_fp),
            system(),
            control()
        {
            clock = 0;
        }

        void mainLoop(){
            while (!control.getInterrupt()) {
                if (!clock){
                    control.onLowStepClock();
                    memory.onLowStepClock(&control);
                    system.onLowStepClock(&control);
                    if (control.branchSignals()){
                        system.onLowStepClock(&control);
                    }
                    cout << clock << ' ' << control.getStep() << endl;
                }
                else {
                    cout << clock << ' ' << control.getStep() << endl;
                }
                //update out
                waitForEnter();
                clock = !clock;
            }
        }
};

int main(int argc, char **argv){
    FILE *ebf_fp = fopen(argv[1], "r");
    StepEmulator emulator(ebf_fp);
    emulator.mainLoop();
    fclose(ebf_fp);
    return 0;
}

