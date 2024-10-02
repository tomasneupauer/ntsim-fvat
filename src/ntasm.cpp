#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char *INSTRUCTIONS[16] = {"MVW", "LDW", "STW", "PSH", "POP", "INB", "OUB", "JNZ", "HNZ", "CMP", "AND", "ORR", "NOR", "SFR", "ADC", "SBB"};

int next_token(FILE *fp, char *token){
    return fscanf(fp, "%7s", token) > 0;
}

void write_instr(FILE *fp, char *instr, char *reg, char mode){
     int mode_bit = mode == 'I';
     int op_code=0;
     while (!strcmp(instr, INSTRUCTIONS[i]){
        op_code++;
     }
     fputc((op_code << 4) | (mode_bit << 3) | (reg[0] - 'A'), fp);
}

void write_imm8(FILE *fp, char *immidiate){
     fputc(strtol(immidiate, NULL, 0, fp);
}

void write_imm16();

int main(int argc, char **argv){
    char name[256];
    char out[256];
    scanf("%s%s", name, out);
    FILE *asm_fp = fopen(name, "r");
    FILE *ebf_fp = fopen(out, "w");
    char version[16];
    char title[256];
    char author[256];
    fgets(version, sizeof(version), asm_fp);
    fgets(title, sizeof(title), asm_fp);
    fgets(author, sizeof(author), asm_fp);
    char instr[8];
    while (next_token(asm_fp, instr)){
        char arg_a[8];
        char arg_b[8];
        if (!strcmp(instr, "MVW") || !strcmp(instr, "INB") || !strcmp(instr, "OUB")){
            next_token(asm_fp, arg_a);
            next_token(asm_fp, arg_b);
            if (strlen(arg_a) == 1){
                write_instr(ebf_fh, instr, arg_a, 'R');
                write_instr(ebf_fh, instr, arg_b, 'R');
            }
            else {
                write_instr(ebf_fh, instr, arg_b, 'I');
                write_imm8(ebf_fh, arg_a);
            }
        }
    }
    fclose(asm_fp);
    return 0;
}

