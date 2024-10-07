#include <iostream>
#include <cstdio>
#include <cstring>
#include "globals.hpp"
using namespace std;

int instr_opcode(char *instr){
    return find(INSTRUCTIONS.begin(), INSTRUCTIONS.end(), (string)instr) - INSTRUCTIONS.begin();
}

int next_token(FILE *fp, char *token){
    return fscanf(fp, "%7s", token) > 0;
}

void write_instr(FILE *fp, int opcode, char reg, char mode){
    int mode_bit = mode == 'I';
    fputc((opcode << 4) | (mode_bit << 3) | (reg - 'A'), fp);
}

void write_imm8(FILE *fp, char *immidiate){
    fputc(strtol(immidiate, NULL, 0), fp);
}

void write_imm16(FILE *fp, char *immidiate){
    long imm = strtol(immidiate, NULL, 0);
    fputc(imm, fp);
    fputc(imm >> 8, fp);
};

int assemble(FILE *infp, FILE *oufp){
    char instr[8];
    char arg_a[8];
    char arg_b[8];
    while (next_token(infp, instr)){
        int opcode = instr_opcode(instr);
        if (opcode == 0 || opcode == 5 || opcode == 6 || opcode >= 9 && opcode <= 15){
            next_token(infp, arg_a);
            next_token(infp, arg_b);
            if (strlen(arg_b) == 1){
                write_instr(oufp, opcode, arg_b[0], 'R');
                write_instr(oufp, opcode, arg_a[0], 'R');
            }
            else {
                write_instr(oufp, opcode, arg_a[0], 'I');
                write_imm8(oufp, arg_b);
            }
        }
        else if (opcode == 1 || opcode == 2){
            next_token(infp, arg_a);
            if (strlen(arg_a) == 1){
                write_instr(oufp, opcode, arg_a[0], 'R');
            }
            else {
                next_token(infp, arg_b);
                write_instr(oufp, opcode, arg_b[0], 'I');
                write_imm16(oufp, arg_a);
            }
        }
        else if (opcode == 3 || opcode == 4 || opcode == 7 || opcode == 8){
            next_token(infp, arg_a);
            if (strlen(arg_a) == 1){
                write_instr(oufp, opcode, arg_a[0], 'R');
            }
            else {
                write_instr(oufp, opcode, 'A', 'I');
                write_imm8(oufp, arg_a);
            }
        }
    }
    return 0;
}

int main(int argc, char **argv){
    FILE *asm_fp = fopen(argv[1], "r");
    FILE *ebf_fp = fopen(argv[2], "w");
    char version[16];
    char title[256];
    char author[256];
    fgets(version, sizeof(version), asm_fp);
    fgets(title, sizeof(title), asm_fp);
    fgets(author, sizeof(author), asm_fp);
    assemble(asm_fp, ebf_fp);
    fclose(asm_fp);
    fclose(ebf_fp);
    return 0;
}

