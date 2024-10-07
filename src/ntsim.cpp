#include <iostream>
#include <cstdio>
#include "control.hpp"
#include "bridge.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "ascii-render.hpp"
using namespace std;

#define VIDEO_SIZE 65536

class StepEmulator{
    private:
        Control control;
        Bridge bridge;
        Memory memory;
        System system;
        bool clock;

    public:
        StepEmulator(FILE *ebf_fp):
            memory(ebf_fp, VIDEO_SIZE),
            control(),
            bridge(),
            system()
        {
            clock = 0;
        }

        void mainLoop(){
            while (!control.getInterruptFlags()) {
                if (!clock){
                    control.onLowStepClock();
                    bridge.onLowStepClock(&control);
                    memory.onLowStepClock(&control);
                    system.onLowStepClock(&control);
                    if (control.branchSignals()){
                        system.onLowStepClock(&control);
                    }
                }
                else {
                    control.onHighStepClock();
                    bridge.onHighStepClock(&control);
                    memory.onHighStepClock(&control);
                    system.onHighStepClock(&control);
                }
                cout << clock << endl;
                control.dumpControl();
                system.dumpSystem();
                bridge.dumpBridge();
                updateAsciiRender(&control, &bridge, &system, &memory, clock);
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

