#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

vector<string> SIGNALS = {"LX", "LY", "LR", "LF", "LG", "LH", "LM", "LI", "LP", "EZ", "EF", "ER", "AR", "AC", "AS", "RC", "IC", "IS", "DS", "PI", "PO", "RI", "RO", "MO", "XT", "HF"};

vector<vector<int>> MICROCODE= {
    
}

typedef unsigned char byte_t;
typedef unsigned short int addr_t;
typedef bool signal_t;
typedef int bus_t;

class Memory{
    private:
        byte_t *mem_block;
        size_t mem_size;
        byte_t mem_bank;
        byte_t exc_bank;
    
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

        void onLowStepClock(){
            
        }

        void dumpMemory(){
            for (int i=0; i<mem_size; i++){
                printf("0x%02X\n", mem_block[i]);
            }
        }
};

class System{
    private:
        vector<byte_t> gp_regs;
        vector<byte_t> xy_regs;
        addr_t program_counter;
        addr_t stack_pointer;
        addr_t memory_address;

    public:
        System():
            gp_regs(8, 0);
            xy_regs(8, 0);
        {
            program_counter = 0;
            stack_pointer = 0;
        }

        void onLowStepClock(){
        
        }
};

//control public


class Control{
    private:
        bus_t data_bus;
        bus_t addr_bus;
        byte_t opcode;
        byte_t step;
        vector<signal_t> signals;

        Control():
            signals(SIGNAL.size(), 0);
        {
            resetBuses();
            opcode = 0;
            step = -1;
        }

        void resetBuses(){
            data_bus = -1;
            addr_bus = -1;
        }

        void resolveState(){
            int state = opcode & 0xf8 | step & 0x07;
            for (int i=0; i<signals.size(); i++){
                signals[i] = find(MICROCODE[i].begin(), MICROCODE[i].end(), state) != MICROCODE[i].end();
            }
        }
        
    public:
        void onLowStep(){
            if (!signalValue(signals, "XT"){
                step++;
            }
            else {
                step = 0;
            }
            resetBuses();
            resolveState();
        }

        signal_t signalValue(vector<signal_t> signals, string name){
            int index = find(SIGNALS.begin(), SIGNALS.end(), name) - SIGNALS.begin();
            if (index < signals.size()){
                return signals[index];
            }
            return 0;
        }
}

void waitForEnter(){
    cout << "Press ENTER to continue";
    cout.flush();
    string null;
    getline(cin, null);
}

class StepEmulator{
    private:
        Memory memCtl;
        System sysCtl;
        bool clock;

    public:
        StepEmulator(FILE *ebf_fp):
            memCtl(ebf_fp),
            sysCtl()
        {
            clock = 0;
        }

        void mainLoop(){
            while (1) {
                if (!clock){
                    sysCtl.onLowStepClock();
                    cout << clock << endl;
                }
                else {
                    cout << clock << endl;
                }
                //update out
                waitForEnter();
                clock = !clock;
            }
        }
};

//class Registers{};
//class Pointers{};
//class Buses{};

int main(int argc, char **argv){
    FILE *ebf_fp = fopen(argv[1], "r");
    StepEmulator emulator(ebf_fp);
    emulator.mainLoop();
    fclose(ebf_fp);
    return 0;
}

