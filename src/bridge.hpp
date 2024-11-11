#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "globals.hpp"
#include "control.hpp"
using namespace std;

class Bridge{
    private:
        byte_t portRegister;

        void setPortSignals(vector<signal_t> *portSignals, signal_t portIn, signal_t portOut){
            int portState = portIn << 4 | portOut << 3 | (portRegister & 0x07);
            for (size_t i=0; i<portSignals->size(); i++){
                (*portSignals)[i] = translateState(&LOOPBACK_TABLE[i], portState);
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

        int getPortRegister(){
            return portRegister;
        }

        void dumpBridge(){
            printf("PR - 0x%02X\n", portRegister);
        }
};

#endif

