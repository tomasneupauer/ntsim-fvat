# Circuits

- [Arithmetic Logic Unit](#arithmetic-logic-unit)
- [General Purpose Registers](#general-purpose-registers)

## Arithmetic Logic Unit

- Description:
  - Performs arithmetic and logic operations on a pair of bytes
  - Stores operands in internal registers
  - Updates flag register after each operation
- Inputs:
  - D - Input byte
  - O - OP Code
  - LX - Load register X
  - LY - Load register Y
  - EZ - Output result Z
  - EF - Output flags
  - R - Reset control
  - C - Clock control
  - i - Carry / Borrow in
- Outputs:
  - S - Result byte
- Function:
  - 0x9X - `CMP(X, Y) -> S`
  - 0xAX - `AND(X, Y) @ CMP(X, Y) -> S`
  - 0xBX - `OR(X, Y) @ CMP(X, Y) -> S`
  - 0xCX - `NOR(X, Y) @ CMP(X, Y) -> S`
  - 0xDX - `SFT(X) @ CMP(X, Y) -> S`
  - 0xEX - `ADC(X, Y, i) @ CMP(X, Y) -> S`
  - 0xFX - `SBB(X, Y, i) @ CMP(X, Y) -> S`

## General Purpose Registers

- Description:
  - Contains 8 general purpose registers
  - Register F is reserved for storing flags
  - Registers G and H are reserved for outputing to address bus
- Inputs:
  - D - Input byte
  - O - OP Code
  - LR - Load register A-H
  - LF - Load flags
  - LG - Load low address byte
  - LH - Load high address byte
  - ER - Output from register A-H
  - EA - Output address
  - R - Reset control
  - C - Clock control
- Outputs:
  - Q - Stored byte
  - A - Stored address
  - i - Carry / Borrow flag
- Function:
  - LR - `D -> REG(A-H) ( OP & 0x07 )`
  - LF - `D -> REG(F)`
  - LG - `D -> REG(G)`
  - LH - `D -> REG(H)`
  - ER - `REG(A-H) -> Q ( OP & 0x07 )`
  - EA - `( REG(H) << 8 ) | REG(G) -> A`

