#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "globals.hpp"
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

        int getCarryFlag(){
            return generalPurposeRegisters[5] & 0x01;
        }

        void onLowStepClock(Control *control){
            if (control->signalValue("EZ")){
                int selector = control->getOpcode() >> 4;
                byte_t registerZ = registerX;
                switch (selector){
                    case 10:
                        registerZ = registerX & registerY;
                        break;
                    case 11:
                        registerZ = registerX | registerY;
                        break;
                    case 12:
                        registerZ = ~(registerX | registerY);
                        break;
                    case 13:
                        registerZ = registerX >> 1 & getCarryFlag() << 7;
                        break;
                    case 14:
                        registerZ = registerX + registerY + getCarryFlag();
                        break;
                    case 15:
                        registerZ = registerX - registerY + getCarryFlag();
                        break;
                }
                control->setDataBus(registerZ);
            }
            if (control->signalValue("EF")){
                int selector = control->getOpcode() >> 4;
                byte_t flags = (registerX > registerY) << 1 | (registerX < registerY) << 2 | (registerX == registerY) << 3;
                switch (selector){
                    case 13:
                        flags |= registerX & 0x01;
                        break;
                    case 14:
                        flags |= (registerX + registerY + getCarryFlag()) > 255;
                        break;
                    case 15:
                        flags |= (registerX - registerY + getCarryFlag()) >= 0;
                        break;
                }
                control->setDataBus(flags);
            }
            if (control->signalValue("ER")){
                int selector = control->getOpcode() & 0x07;
                control->setDataBus(generalPurposeRegisters[selector]);
            }
            if (control->signalValue("AR")){
                control->setAddressBus((addr_t)generalPurposeRegisters[7] << 8 & generalPurposeRegisters[6]);
                
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
            if (control->signalValue("IC")){
                programCounter++;
            }
            if (control->signalValue("IS")){
                stackPointer++;
            }
            if (control->signalValue("DS")){
                stackPointer--;
            }
        }
};

#endif

