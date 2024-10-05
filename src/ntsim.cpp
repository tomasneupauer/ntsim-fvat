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
        addr_t memoryAddressRegister;
        byte_t instructionRegister;
        byte_t stepCounter;
        bus_t dataBus;
        bus_t addressBus;
        int interruptFlags;
        int signalState;

        void resetBuses(){
            dataBus = -1;
            addressBus = -1;
        }

        void updateSignals(){
            signalState = instructionRegister & 0xf8 | stepCounter & 0x07;
            for (int i=0; i<signals.size(); i++){
                signals[i] = find(MICROCODE[i].begin(), MICROCODE[i].end(), signalState) != MICROCODE[i].end();
            }
        }

    public:
        Control():
            signals(SIGNALS.size(), 0)
        {
            resetBuses();
            memoryAddressRegister = 0;
            instructionRegister = 0;
            stepCounter = -1;
            interruptFlags = 0;
            signalState = 0;
        }

        signal_t signalValue(string name){
            int index = find(SIGNALS.begin(), SIGNALS.end(), name) - SIGNALS.begin();
            if (index < signals.size()){
                return signals[index];
            }
            return 0;
        }

        void setInterruptFlag(string flag){
            int index = find(INTERRUPTS.begin(), INTERRUPTS.end(), flag) - INTERRUPTS.begin();
            if (index < INTERRUPTS.size()){
                interruptFlags |= 0x01 << index;
            }
        }

        void setDataBus(byte_t data){
            dataBus = data;
        }

        byte_t getDataBus(){
            return dataBus;
        }

        void setAddressBus(addr_t address){
            addressBus = address;
        }

        addr_t getAddressBus(){
            return addressBus;
        }

        void onLowStepClock(){
            if (!signalValue("XT")){
                stepCounter++;
            }
            else {
                stepCounter = 0;
            }
            resetBuses();
            updateSignals();
        }

        void onHighStepClock(){
            if (signalValue("LM")){
                memoryAddressRegister = addressBus;
            }
            if (signalValue("LI")){
                instructionRegister = dataBus;
            }
        }

        int branchSignals(){
            if (dataBus != 0){
                if (signalState == 114 || signalState == 123){
                    signals[signalValue("AR")] = 1;
                    signals[signalValue("RC")] = 1;
                    return 1;
                }
                else if (signalState == 130 || signalState == 139){
                    setInterruptFlag("HLT");
                    return 1;
                }
            }
            else if (signalState == 123 || signalState == 139){
                signals[signalValue("IC")] = 1;
                return 1;
            }
            return 0;
        }

        int getOpcode(){
            return instructionRegister;
        }

        int getStep(){
            return stepCounter;
        }

        int getInterruptFlags(){
            return interruptFlags;
        }

        void dumpSignals(){
            for (int i=0; i<signals.size(); i++){
                cout << signals[i] << ' ';
            }
            cout << endl;
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
        vector<byte_t> generalPurposeRegisters;
        addr_t programCounter;
        addr_t stackPointer;
        byte_t registerX;
        byte_t registerY;

    public:
        System():
            generalPurposeRegisters(8, 0)
        {
            program_counter = 0;
            stack_pointer = 0;
            registerX = 0;
            registerY = 0;
        }

        int getCarryFlag(){
            return generalPurposeRegisters[5] & 0x01;
        }

        void onLowStepClock(Control *control){
            if (control->signalValue("EZ"){
                int selector = control.getOpcode() >> 4;
                byte_t registerZ = registerX;
                switch (selector){
                    case 10:
                        registerZ = registerX & registerY;
                        break;
                    case 11:
                        registerZ = registerX | registerY;
                        break;
                    case 12:
                        registerZ = ~(registerX | registerY);
                        break;
                    case 13:
                        registerZ = registerX >> 1 & getCarryFlag() << 7;
                        break;
                    case 14:
                        registerZ = registerX + registerY + getCarryFlag();
                        break;
                    case 15:
                        registerZ = registerX - registerY + getCarryFlag();
                        break;
                }
                control->setDataBus(registerZ);
            }
            if (control->signalValue("EF"){
                int selector = control.getOpcode() >> 4;
                byte_t flags = (registerX > registerY) << 1 | (registerX < registerY) << 2 | (registerX == registerY) << 3;
                switch (selector){
                    case 13:
                        flags |= registerX & 0x01;
                        break;
                    case 14:
                        flags |= (registerX + registerY + getCarryFlag()) > 255;
                        break;
                    case 15:
                        flags |= (registerX - registerY + getCarryFlag()) >= 0;
                        break;
                }
                control->setDataBus(flags);
            }
            if (control->signalValue("ER"){
                int selector = control.getOpcode() & 0x07;
                control->setDataBus(generalPurposeRegisters[selector]);
            }
            if (control->signalValue("AR"){
                control->setAddressBus((addr_t)generalPurposeRegisters[7] << 8 & generalPurposeRegisters[6]);
                
            }
            if (control->signalValue("AC"){
                control->setAddressBus(programCounter);
            }
            if (control->signalValue("AS"){
                control->setAddressBus(stackPointer);
            }
            if (control-signalValue("IC" && programCounter == 0xffff){
                control->setInterruptFlag("COF");
            }
            if (control-signalValue("IS" && stackPointer == 0xffff){
                control->setInterruptFlag("SOF");
            }
            if (control-signalValue("DS" && stackPointer == 0x0000){
                control->setInterruptFlag("SOF");
            }
        }

        void onHighStepClock(Control *control){
            if (control->signalValue("LX"){
                registerX = control->getDataBus();
            }
            if (control->signalValue("LY"){
                registerY = control->getDataBus();
            }
            if (control->signalValue("LR"){
                int selector = control.getOpcode() & 0x07;
                generalPurposeRegisters[selector] = control->getDataBus();
            }
            if (control->signalValue("LF"){
                generalPurposeRegisters[5] = control->getDataBus();
            }
            if (control->signalValue("LG"){
                generalPurposeRegisters[6] = control->getDataBus();
            }
            if (control->signalValue("LH"){
                generalPurposeRegisters[7] = control->getDataBus();
            }
            if (control->signalValue("IC"){
                
            }
            if (control->signalValue("IS"){
                
            }
            if (control->signalValue("DS"){
                
            }
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
            while (!control.getInterruptFlags()) {
                if (!clock){
                    control.onLowStepClock();
                    memory.onLowStepClock(&control);
                    system.onLowStepClock(&control);
                    if (control.branchSignals()){
                        system.onLowStepClock(&control);
                    }
                    cout << clock << ' ' << control.getStep() << endl;
                    control.dumpSignals();
                }
                else {
                    cout << clock << ' ' << control.getStep() << endl;
                    control.dumpSignals();
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

