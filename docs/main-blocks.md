# Main Blocks

- [Central Control Unit - CCU](#central-control-unit---ccu)
- [Arithmetic Logic Unit - ALU](#arithmetic-logic-unit---alu)
- [General Purpose Registers - GPR](#general-purpose-registers---gpr)
- [Program Counter - PC](#program-counter---pc)
- [Stack Pointer - SP](#stack-pointer---sp)
- [Memory Address Register - MAR](#memory-address-register---mar)
- [Instruction Register - IR](#instruction-register---ir)
- [Step Counter - SC](#step-counter---sc)

## Central Control Unit - CCU

- Description:
  - Decodes current instruction to microcode
- Inputs:
  - D - Input data
  - O - OP Code
  - T - Current step
- Outputs:
  - LX - Load ALU register X
  - LY - Load ALU register Y
  - EZ - Enable ALU result Z
  - EF - Enable ALU flags
  - LR - Load GPR register A-H
  - LF - Load GPR flag register F
  - LG - Load GPR low address register G
  - LH - Load GPR high address register H
  - ER - Enable GPR register A-H
  - AR - Enable GPR GH address
  - IC - Increment PC address
  - RC - Load PC address
  - AC - Enable PC address
  - IS - Increment SP address
  - DS - Decrement SP address
  - AS - Enable SP address
  - LM - Load memory address register
  - LI - Load instruction register
  - XT - Reset step counter
  - LP - Load port register
  - PI - Port input signal
  - PO - Port output signal
  - RI - Random access memory input signal
  - RO - Random access memory output signal
  - MO - Program memory output signal
  - HLT - Halt flag
- Function:
  - For detailed function see [Microcode](microcode.md)

## Arithmetic Logic Unit - ALU

- Description:
  - Performs arithmetic and logic operations on a pair of bytes
  - Stores operands in internal registers
  - Updates flag register after each operation
- Inputs:
  - D - Input data
  - O - OP Code
  - LX - Load ALU register X
  - LY - Load ALU register Y
  - EZ - Enable ALU result Z
  - EF - Enable ALU flags
  - R - Reset control
  - C - Clock control
  - i - Carry / Borrow in
- Outputs:
  - D - Output data
- Function:
  - LX - `D -> X`
  - LY - `D -> Y`
  - EZ - `Z -> D`
  - EF - `F -> D`
  - 0x9X - `CMP(X, Y) -> F`
  - 0xAX - `CMP(X, Y) -> F @ AND(X, Y) -> Z`
  - 0xBX - `CMP(X, Y) -> F @ OR(X, Y) -> Z`
  - 0xCX - `CMP(X, Y) -> F @ NOR(X, Y) -> Z`
  - 0xDX - `CMP(X, Y) -> F @ SFT(X, Y) -> Z`
  - 0xEX - `CMP(X, Y) -> F @ ADC(X, Y, i) -> Z`
  - 0xFX - `CMP(X, Y) -> F @ SBB(X, Y, i) -> Z`

## General Purpose Registers - GPR

- Description:
  - Contains 8 general purpose registers
  - Register F is reserved for storing flags
  - Registers G and H are reserved for outputing to address bus
- Inputs:
  - D - Input data
  - O - OP Code
  - LR - Load GPR register A-H
  - LF - Load GPR flag register F
  - LG - Load GPR low address register G
  - LH - Load GPR high addres register H
  - ER - Enable GPR register A-H
  - AR - Enable GPR GH address
  - R - Reset control
  - C - Clock control
- Outputs:
  - D - Output data
  - A - Output address
  - i - Carry / Borrow flag
- Function:
  - LR - `D -> REG(A-H) ( OP & 0x07 )`
  - LF - `D -> REG(F)`
  - LG - `D -> REG(G)`
  - LH - `D -> REG(H)`
  - ER - `REG(A-H) -> D ( OP & 0x07 )`
  - AR - `( REG(H) << 8 ) | REG(G) -> A`

## Program Counter - PC

- Description:
  - Points to the next instruction in memory
  - Address is stored in a pair of registers
  - Increments stored address
- Inputs:
  - D - Input data
  - A - Input address
  - IC - Increment PC address
  - LC - Load PC data
  - RC - Load PC address
  - EC - Enable PC data
  - AC - Enable PC address
  - SE - Select signal
  - R - Reset control
  - C - Clock control
- Outputs:
  - D - Output data
  - A - Output address
  - COF - Counter overflow flag
- Function:
  - IC - `PC(G) + 1 -> PC(G+) @ PC(H) + ( PC(G+) > 255 ) -> PC(H+)`
  - LC - `D -> PC(S) ( 0-G 1-H )`
  - RC - `( A & 255 ) -> PC(G) @ ( A >> 8 ) -> PC(H)`
  - EC - `PC(S) -> D ( 0-G 1-H )`
  - AC - `( PC(H) << 8 ) | PC(G) -> A`
  - `PC(H+) > 255 -> COF`

## Stack Pointer - SP

- Description:
  - Points to the top of stack memory
  - Address is stored in a pair of registers
  - Increments or decrements stored adderess
- Inputs:
  - D - Input data
  - IS - Increment SP address
  - DS - Decrement SP address
  - LS - Load SP data
  - ES - Enable SP data
  - AS - Enable SP address
  - SE - Select signal
  - R - Reset control
  - C - Clock control
- Outputs:
  - D - Output data
  - A - Output address
  - SOF - Stack overflow flag
- Function:
  - IS - `SP(G) + 1 -> SP(G+) @ SP(H) + ( SP(G+) > 255 ) -> SP(H+)`
  - DS - `SP(G) - 1 -> SP(G-) @ SP(H) - ( SP(G-) < 0 ) -> SP(H-)`
  - LS - `D -> SP(S) ( 0-G 1-H )`
  - ES - `SP(S) -> D ( 0-G 1-H )`
  - AS - `( SP(H) << 8 ) | SP(G) -> A`
  - `( PC(H+) > 255 ) | ( PC(H-) < 0 ) -> SOF`

## Memory Adderss Register - MAR

- Description:
  - Points to data in the random access memory
  - Outputs address to the memory control unit
- Inputs:
  - A - Input address
  - LM - Load memory address register
  - R - Reset control
  - C - Clock control
- Outputs:
  - A - Output address
- Function:
  - LM - `A -> MAR`

## Instruction Register - IR

- Description:
  - Stores current instruction
- Inputs:
  - D - Input data
  - LI - Load instruction register
  - R - Reset control
  - C - Clock control
- Outputs:
  - O - OP Code
- Function:
  - LI - `D -> IR`
  - `IR -> O`

## Step Counter - SC

- Description:
  - Stores current step
  - Increments and resets current step
- Inputs:
  - CLK - Master clock
  - HLT - Halt flag
  - INT - Interrupt flag
  - COF - Counter overflow flag
  - SOF - Stack overflow flag
  - XT - Reset step counter
  - R - Reset control
- Outputs:
  - T - Current step
  - C - Clock control
- Function:
  - XT - `~XT ? 0 : ( SC + 1 ) -> SC+`
  - `~( HLT | INT | COF | SOF ) & CLK -> C`
  - `SC -> T`

