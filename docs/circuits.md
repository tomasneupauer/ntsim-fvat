# Circuits

- [Arithmetic Logic Unit](#arithmetic-logic-unit)
- [General Purpose Registers](#general-purpose-registers)
- [Program Counter](#program-counter)
- [Stack Pointer](#stack-pointer)

## Arithmetic Logic Unit

- Description:
  - Performs arithmetic and logic operations on a pair of bytes
  - Stores operands in internal registers
  - Updates flag register after each operation
- Inputs:
  - D - Input data
  - O - OP Code
  - LX - Load register X
  - LY - Load register Y
  - EZ - Enable result Z
  - EF - Enable flags
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

## General Purpose Registers

- Description:
  - Contains 8 general purpose registers
  - Register F is reserved for storing flags
  - Registers G and H are reserved for outputing to address bus
- Inputs:
  - D - Input data
  - O - OP Code
  - LR - Load register data
  - LF - Load flags byte
  - LG - Load low address byte
  - LH - Load high address byte
  - ER - Enable register data
  - AR - Enable register address
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

## Program Counter

- Description:
  - Points to the next instruction in memory
  - Address is stored in a pair of registers
  - Increments stored address
- Inputs:
  - D - Input data
  - A - Input address
  - IC - Increment program counter
  - LC - Load program counter data
  - RC - Load program counter address
  - EC - Enable program counter data
  - AC - Enable program counter address
  - S - Select control
  - R - Reset control
  - C - Clock control
- Outputs:
  - D - Output data
  - A - Output address
  - COF - Counter overflow
- Function:
  - IC - `PC(G) + 1 -> PC(G+) @ PC(H) + ( PC(G+) > 255 ) -> PC(H+)`
  - LC - `D -> PC(S) ( 0-G 1-H )`
  - RC - `( A & 255 ) -> PC(G) @ ( A >> 8 ) -> PC(H)`
  - EC - `PC(S) -> D ( 0-G 1-H )`
  - AC - `( PC(H) << 8 ) | PC(G) -> A`
  - `PC(H+) > 255 -> COF`

## Stack Pointer

- Description:
  - Points to the top of stack memory
  - Address is stored in a pair of registers
  - Increments or decrements stored adderess
- Inputs:
  - D - Input data
  - IS - Increment stack pointer
  - DS - Decrement stack pointer
  - LS - Load stack pointer data
  - ES - Enable stack pointer data
  - AS - Enable stack pointer address
  - S - Select control
  - R - Reset control
  - C - Clock control
- Outputs:
  - D - Output data
  - A - Output address
  - SOF - Stack overflow
- Function:
  - IS - `SP(G) + 1 -> SP(G+) @ SP(H) + ( SP(G+) > 255 ) -> SP(H+)`
  - DS - `SP(G) - 1 -> SP(G-) @ SP(H) - ( SP(G-) < 0 ) -> SP(H-)`
  - LS - `D -> SP(S) ( 0-G 1-H )`
  - ES - `SP(S) -> D ( 0-G 1-H )`
  - AS - `( SP(H) << 8 ) | SP(G) -> A`
  - `( PC(H+) > 255 ) | ( PC(H-) < 0 ) -> SOF`

