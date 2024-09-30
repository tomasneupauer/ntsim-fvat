# Circuits

- [Arithmetic Logic Unit](#arithmetic-logic-unit)
- [General Purpose Registers](#general-purpose-registers)
- [Stack Pointer](#stack-pointer)
- [Program Counter](#program-counter)

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
  - T - Output data
- Function:
  - LX - `D -> X`
  - LY - `D -> Y`
  - EZ - `Z -> T`
  - EF - `F -> T`
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
  - LR - Load register
  - LF - Load flags
  - LG - Load low address byte
  - LH - Load high address byte
  - ER - Enable register data
  - AR - Enable reqister address
  - R - Reset control
  - C - Clock control
- Outputs:
  - T - Output data
  - A - Output address
  - i - Carry / Borrow flag
- Function:
  - LR - `D -> REG(A-H) ( OP & 0x07 )`
  - LF - `D -> REG(F)`
  - LG - `D -> REG(G)`
  - LH - `D -> REG(H)`
  - ER - `REG(A-H) -> T ( OP & 0x07 )`
  - AR - `( REG(H) << 8 ) | REG(G) -> A`

## Stack Pointer

- Description:
  - Points to the top of stack memory
  - Address is stored in a pair of registers
  - Increments or decrements stored adderess
- Inputs:
  - D - Input data
  - IS - Increment stack pointer
  - DS - Decrement stack pointer
  - LS - Load stack pointer
  - ES - Enable stack pointer data
  - AS - Enable stack pointer address
  - S - Select control ( 0-Low 1-High )
  - R - Reset control
  - C - Clock control
- Outputs:
  - T - Output data
  - A - Output address
- Function:

