#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "globals.hpp"
#include "control.hpp"
using namespace std;

class System{
    private:
        vector<byte_t> generalPurposeRegisters;
        addr_t programCounter;
        addr_t stackPointer;
        byte_t registerX;
        byte_t registerY;

    public:
        System():
            generalPurposeRegisters(8, 0)
        {
            programCounter = 0;
            stackPointer = 0;
            registerX = 0;
            registerY = 0;
        }

        int getCarryIn(){
            return generalPurposeRegisters[5] & 0x01;
        }

        int getCarryOut(byte_t opcode){
            switch (opcode >> 4){
                case 13:
                    return registerY & 0x01;
                case 14:
                    return (registerX + registerY + getCarryIn()) > 255;
                case 15:
                    return (registerX - registerY + getCarryIn()) >= 0;
            }
            return 0;
        }

        int getRegisterZ(byte_t opcode){
            switch (opcode >> 4){
                case 10:
                    return  registerX & registerY;
                case 11:
                    return registerX | registerY;
                case 12:
                    return ~(registerX | registerY);
                case 13:
                    return registerY >> 1 | getCarryIn() << 7;
                case 14:
                    return registerX + registerY + getCarryIn();
                case 15:
                    return registerX - registerY + getCarryIn();
            }
            return registerX;
        }

        void onLowStepClock(Control *control){
            if (control->signalValue("EZ")){
                control->setDataBus(getRegisterZ(control->getOpcode()));
            }
            if (control->signalValue("EF")){
                byte_t carry = getCarryOut(control->getOpcode());
                byte_t greater = (registerX > registerY) << 1;
                byte_t less = (registerX < registerY) << 2;
                byte_t equal = (registerX == registerY) << 3;
                control->setDataBus(equal | less | greater | carry);
            }
            if (control->signalValue("ER")){
                int selector = control->getOpcode() & 0x07;
                control->setDataBus(generalPurposeRegisters[selector]);
            }
            if (control->signalValue("AR")){
                control->setAddressBus((addr_t)generalPurposeRegisters[7] << 8 | generalPurposeRegisters[6]);
                
            }
            if (control->signalValue("AC")){
                control->setAddressBus(programCounter);
            }
            if (control->signalValue("AS")){
                control->setAddressBus(stackPointer);
            }
            if (control->signalValue("IC") && programCounter == 0xffff){
                control->setInterruptFlag("COF");
            }
            if (control->signalValue("IS") && stackPointer == 0xffff){
                control->setInterruptFlag("SOF");
            }
            if (control->signalValue("DS") && stackPointer == 0x0000){
                control->setInterruptFlag("SOF");
            }
            if (control->signalValue("EC")){
                if (control->signalValue("SE")){
                    control->setDataBus(programCounter >> 8);
                }
                else {
                    control->setDataBus(programCounter);
                }
            }
            if (control->signalValue("ES")){
                if (control->signalValue("SE")){
                    control->setDataBus(stackPointer >> 8);
                }
                else {
                    control->setDataBus(stackPointer);
                }
            }
        }

        void onHighStepClock(Control *control){
            if (control->signalValue("LX")){
                registerX = control->getDataBus();
            }
            if (control->signalValue("LY")){
                registerY = control->getDataBus();
            }
            if (control->signalValue("LR")){
                int selector = control->getOpcode() & 0x07;
                generalPurposeRegisters[selector] = control->getDataBus();
            }
            if (control->signalValue("LF")){
                generalPurposeRegisters[5] = control->getDataBus();
            }
            if (control->signalValue("LG")){
                generalPurposeRegisters[6] = control->getDataBus();
            }
            if (control->signalValue("LH")){
                generalPurposeRegisters[7] = control->getDataBus();
            }
            if (control->signalValue("RC")){
                programCounter = control->getAddressBus();
            }
            if (control->signalValue("IC")){
                programCounter++;
            }
            if (control->signalValue("IS")){
                stackPointer++;
            }
            if (control->signalValue("DS")){
                stackPointer--;
            }
            if (control->signalValue("LC")){
                if (control->signalValue("SE")){
                    programCounter = (programCounter & 0x00ff) | (addr_t)control->getDataBus() << 8;
                }
                else {
                    programCounter = (programCounter & 0xff00) | control->getDataBus();
                }
            }
            if (control->signalValue("LS")){
                if (control->signalValue("SE")){
                    stackPointer = (stackPointer & 0x00ff) | (addr_t)control->getDataBus() << 8;
                }
                else {
                    stackPointer = (stackPointer & 0xff00) | control->getDataBus();
                }
            }
        }

        int getRegister(int selector){
            return generalPurposeRegisters[selector];
        }

        int getRegisterX(){
            return registerX;
        }

        int getRegisterY(){
            return registerY;
        }

        int getProgramCounter(){
            return programCounter;
        }

        int getStackPointer(){
            return stackPointer;
        }

        void dumpSystem(){
            cout << "GP - ";
            for (byte_t reg : generalPurposeRegisters){
                printf("%02X ", reg);
            }
            printf("\nPC - 0x%04X SP - 0x%04X LX - 0x%02X LY 0x%02X\n", programCounter, stackPointer, registerX, registerY);
        }
};

#endif

