#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "globals.hpp"
#include "control.hpp"
using namespace std;

class Bridge{
    private:
        byte_t portRegister;

        void setPortSignals(vector<signal_t> *portSignals, signal_t portIn, signal_t portOut){
            int portState = portIn << 4 | portOut << 3 | portRegister & 0x07;
            for (int i=0; i<portSignals->size(); i++){
                (*portSignals)[i] = find(LOOPBACK_TABLE[i].begin(), LOOPBACK_TABLE[i].end(), portState) != LOOPBACK_TABLE[i].end();
            }
        }

    public:
        Bridge (){
            portRegister = 0;
        }

        void onLowStepClock(Control *control){
            setPortSignals(control->getPortSignalsPtr(), control->signalValue("PI"), control->signalValue("PO"));
            // port device output
        }

        void onHighStepClock(Control *control){
            if (control->signalValue("LP")){
                portRegister = control->getDataBus();
            }
            // port device input
        }

        byte_t getPortRegister(){
            return portRegister;
        }

        void dumpBridge(){
            printf("PR - 0x%02X\n", portRegister);
        }
};

#endif

