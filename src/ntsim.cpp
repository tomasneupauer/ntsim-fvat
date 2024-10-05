#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "control.hpp"
#include "system.hpp"
#include "memory.hpp"
using namespace std;

#define VIDEO_SIZE 65536

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

class StepEmulator{
    private:
        Memory memory;
        System system;
        Control control;
        bool clock;

    public:
        StepEmulator(FILE *ebf_fp):
            memory(ebf_fp, VIDEO_SIZE),
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

