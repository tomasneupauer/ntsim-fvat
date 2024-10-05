#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <vector>
#include "globals.hpp"
#include "control.hpp"
using namespace std;

class Bridge{
    private:
        byte_t portRegister;

        void setPortSignals(vector<signal_t> *portSignals, signal_t portIn, signal_t portOut){
            int portState = portIn << 4 | portOut << 3 | portRegister & 0x07;
            for (int i=0; i<portSignals; i++){
                *portSignals[i] = find(LOOPBACK_TABLE[i].begin(), LOOPBACK_TABLE[i].end(), portState) != LOOPBACK_TABLE[i].end();
            }
        }

    public:
        Bridge ():
            portSignals(PORT_SIGNALS.size(), 0)
        {
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
};

#endif

