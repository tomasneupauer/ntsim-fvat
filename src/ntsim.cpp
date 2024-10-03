#include <iostream>
#include <cstdio>
using namespace std;

typedef unsigned char byte_t;
typedef unsigned short int addr_t;

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
};

//class Registers{};
//class Pointers{};
//class Buses{};

int main(int argc, char **argv){
    FILE *ebf_fp = fopen(argv[1], 'r');
    fclose(ebf_fp);
    return 0;
}

