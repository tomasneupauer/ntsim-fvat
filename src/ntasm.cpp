#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char *INSTRUCTIONS[16] = {"MVW", "LDW", "STW", "PSH", "POP", "INB", "OUB", "JNZ", "HNZ", "CMP", "AND", "ORR", "NOR", "SFR", "ADC", "SBB"};

int op_code(char *instr){
    int op = 0;
    while (!strcmp(instr, INSTRUCTIONS[op] && op < 16){
        op++;
    }
    return op;
}

int next_token(FILE *fp, char *token){
    return fscanf(fp, "%7s", token) > 0;
}

void write_instr(FILE *fp, char *instr, char *reg, char mode){
    int mode_bit = mode == 'I';
    fputc((op_code(instr) << 4) | (mode_bit << 3) | (reg[0] - 'A'), fp);
}

void write_imm8(FILE *fp, char *immidiate){
    fputc(strtol(immidiate, NULL, 0) fp);
}

void write_imm16(FILE *fp, char *immidiate){
    long imm = strtol(immidiate, NULL, 0);
    fputc(imm, fp);
    fputc(imm >> 8, fp);
};

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
        int op = op_code(instr);
        char arg_a[8];
        char arg_b[8];
        if (op == 0 || op == 5 || op == 6){
            next_token(asm_fp, arg_a);
            next_token(asm_fp, arg_b);
            if (strlen(arg_a) == 1){
                write_instr(ebf_fp, instr, arg_a, 'R');
                write_instr(ebf_fp, instr, arg_b, 'R');
            }
            else {
                write_instr(ebf_fp, instr, arg_b, 'I');
                write_imm8(ebf_fp, arg_a);
            }
        }
        if (op == 1 || op == 2){
            next_token(asm_fp, arg_a);
            if (strlen(arg_a) == 1){
                write_instr(ebf_fp, instr, arg_a, 'R');
            }
            else {
                next_token(asm_fp, arg_b);
                write_instr(ebf_fp, instr, arg_b, 'I');
                write_imm16(ebf_fp, arg_a);
            }
        }
        else if (op == 3 || op == 4 || op == 7 || op == 8){
            next_token(asm_fp, arg_a);
            if (strlen(arg_a == 1){
                write_instr(ebf_fp, instr, arg_a, 'R');
            }
            else {
                write_instr(ebf_fp, instr, "A", 'I');
                write_imm8(ebf_fp, arg_a);
            }
        }
        else if (op >= 9 && op <=15){
            next_token(asm_fp, arg_a);
            next_token(asm_fp, arg_b);
            if (strlen(arg_b) == 1){
                write_instr(ebf_fp, instr, arg_a, 'R');
                write_instr(ebf_fp, instr, arg_b, 'R');
            }
            else {
                write_instr(ebf_fp, instr, arg_a, 'I');
                write_imm8(ebf_fp, arg_b);
            }
        }
    }
    fclose(asm_fp);
    fclose(ebf_fp);
    return 0;
}

