#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "globals.hpp"
using namespace std;

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

#endif

