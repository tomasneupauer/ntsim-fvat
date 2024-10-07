#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "globals.hpp"
using namespace std;

class Control{
    private:
        vector<signal_t> signals;
        vector<signal_t> portSignals;
        addr_t memoryAddressRegister;
        byte_t instructionRegister;
        byte_t stepCounter;
        bus_t dataBus;
        bus_t addressBus;
        int interruptFlags;
        int signalState;

        void resetBuses(){
            dataBus = 0;
            addressBus = 0;
        }

        void updateSignals(){
            signalState = instructionRegister & 0xf8 | stepCounter & 0x07;
            for (int i=0; i<signals.size(); i++){
                signals[i] = find(MICROCODE[i].begin(), MICROCODE[i].end(), signalState) != MICROCODE[i].end();
            }
        }

    public:
        Control():
            signals(SIGNALS.size(), 0),
            portSignals(PORT_SIGNALS.size(), 0)
        {
            resetBuses();
            memoryAddressRegister = 0;
            instructionRegister = 0;
            stepCounter = -1;
            interruptFlags = 0;
            signalState = 0;
        }

        int signalIndex(vector<string> *set, string name){
            return find(set->begin(), set->end(), name) - set->begin();
        }

        long_addr_t longAddress(byte_t memoryBank){
            return ((long_addr_t)memoryBank & 0x7f) << 16 | memoryAddressRegister;
        }

        signal_t signalValue(string name){
            int index = signalIndex(&SIGNALS, name);
            if (index < signals.size()){
                return signals[index];
            }
            index = signalIndex(&PORT_SIGNALS, name);
            if (index < portSignals.size()){
                return portSignals[index];
            }
            return 0;
        }

        void setInterruptFlag(string flag){
            int index = signalIndex(&INTERRUPTS, flag);
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
                    signals[signalIndex(&SIGNALS, "AR")] = 1;
                    signals[signalIndex(&SIGNALS, "RC")] = 1;
                    return 1;
                }
                else if (signalState == 130 || signalState == 139){
                    setInterruptFlag("HLT");
                    return 1;
                }
            }
            else if (signalState == 123 || signalState == 139){
                signals[signalIndex(&SIGNALS, "IC")] = 1;
                return 1;
            }
            return 0;
        }

        int getMemoryAddressRegister(){
            return memoryAddressRegister;
        }

        int getOpcode(){
            return instructionRegister;
        }

        int getStepCounter(){
            return stepCounter;
        }

        int getInterruptFlags(){
            return interruptFlags;
        }

        vector<signal_t> *getPortSignalsPtr(){
            return &portSignals;
        }

        void dumpControl(){
            cout << "SIGNALS - ";
            for (int i=0; i<signals.size(); i++){
                if (signals[i]){
                    cout << SIGNALS[i] << ' ';
                }
            }
            cout << "\nPORT SIGNALS - ";
            for (int i=0; i<portSignals.size(); i++){
                if (portSignals[i]){
                    cout << PORT_SIGNALS[i] << ' ';
                }
            }
            printf("\nDATA - 0x%02X ADDR - 0x%04X\n", dataBus, addressBus);
            printf("MAR - 0x%04X IR - 0x%02X STEP - 0x%02X\n", memoryAddressRegister, instructionRegister, stepCounter);
        }
};

#endif

