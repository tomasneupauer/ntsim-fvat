#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <vector>
#include <string>
using namespace std;

typedef unsigned char byte_t;
typedef unsigned short int addr_t;
typedef unsigned int long_addr_t;
typedef bool signal_t;
typedef int bus_t;

vector<string> INSTRUCTIONS = {"MVW", "LDW", "STW", "PSH", "POP", "INB", "OUB", "JNZ", "HNZ", "CMP", "AND", "ORR", "NOR", "SFR", "ADC", "SBB"};

vector<string> SIGNALS = {"LX", "LY", "LR", "LF", "LG", "LH", "LM", "LI", "LP", "EZ", "EF", "ER", "AR", "AC", "AS", "RC", "IC", "IS", "DS", "PI", "PO", "RI", "RO", "MO", "XT"};

vector<string> INTERRUPTS = {"HLT", "INT", "COF", "SOF"};

vector<string> LOOPBACK_SIGNALS = {"LC", "LS", "LB", "EC", "ES", "EB", "SE"};

vector<vector<int> LOOPBACK_PORTS = {
    {8, 9},
    {10, 11},
    {12, 13},
    {0, 1},
    {2, 3},
    {4, 5},
    {1, 3, 5, 9, 11, 13}
}

vector<vector<int>> MICROCODE = {
    {2, 59, 146, 154, 162, 170, 178, 186, 194, 202, 210, 218, 226, 234, 242, 250},
    {148, 155, 164, 171, 180, 187, 196, 203, 212, 219, 228, 235, 244, 251},
    {4, 11, 19, 31, 68, 76, 84, 92, 165, 172, 181, 188, 197, 204, 213, 220, 229, 236, 245, 252},
    {149, 156, 166, 173, 182, 189, 198, 205, 214, 221, 230, 237, 246, 253},
    {27, 43},
    {29, 45},
    {0, 2, 8, 10, 16, 18, 24, 26, 28, 30, 32, 34, 40, 42, 44, 46, 48, 50, 56, 58, 60, 64, 66, 67, 72, 74, 75, 80, 82, 88, 90, 96, 98, 104, 106, 112, 120, 122, 128, 136, 138, 144, 146, 152, 154, 160, 162, 168, 170, 176, 178, 184, 186, 192, 194, 200, 202, 208, 210, 216, 218, 224, 226, 232, 234, 240, 242, 248, 250},
    {1, 3, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 83, 89, 97, 99, 105, 113, 121, 129, 137, 145, 147, 153, 161, 163, 169, 177, 179, 185, 193, 195, 201, 209, 211, 217, 225, 227, 233, 241, 243, 249},
    {82, 91, 98, 107},
    {4, 61, 165, 172, 181, 188, 197, 204, 213, 220, 229, 236, 245, 252},
    {149, 156, 166, 173, 182, 189, 198, 205, 214, 221, 230, 237, 246, 253},
    {2, 35, 47, 51, 82, 98, 100, 108, 114, 130, 146, 148, 154, 162, 164, 170, 178, 180, 186, 194, 196, 202, 210, 212, 218, 226, 228, 234, 242, 244, 250},
    {18, 30, 34, 46},
    {0, 2, 8, 10, 16, 24, 26, 28, 32, 40, 42, 44, 48, 56, 58, 64, 66, 72, 74, 80, 82, 88, 90, 96, 98, 104, 106, 112, 120, 122, 128, 136, 138, 144, 146, 152, 154, 160, 162, 168, 170, 176, 178, 184, 186, 192, 194, 200, 202, 208, 210, 216, 218, 224, 226, 232, 234, 240, 242, 248, 250},
    {50, 60, 67, 75},
    {},
    {1, 3, 9, 11, 17, 25, 27, 29, 33, 41, 43, 45, 49, 57, 59, 65, 73, 81, 83, 89, 91, 97, 99, 105, 107, 113, 121, 129, 137, 145, 147, 153, 155, 161, 163, 169, 171, 177, 179, 185, 187, 193, 195, 201, 203, 209, 211, 217, 219, 225, 227, 233, 235, 241, 243, 249, 251},
    {55, 61},
    {66, 74},
    {100, 108},
    {84, 92},
    {35, 47, 51, 61},
    {19, 31, 68, 76},
    {1, 3, 9, 11, 17, 25, 27, 29, 33, 41, 43, 45, 49, 57, 59, 65, 73, 81, 83, 89, 91, 97, 99, 105, 107, 113, 121, 123, 129, 137, 139, 145, 147, 153, 155, 161, 163, 169, 171, 177, 179, 185, 187, 193, 195, 201, 203, 209, 211, 217, 219, 225, 227, 233, 235, 241, 243, 249, 251},
    {4, 11, 19, 31, 35, 47, 51, 61, 68, 76, 84, 92, 100, 108, 149, 156, 166, 173, 182, 189, 198, 205, 214, 221, 230, 237, 246, 253, 114, 123, 130, 139}
};

#endif

