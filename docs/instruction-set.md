# Instruction Set

## MVW - Move word

- Description:
- Assembly:
  - `MVW    T (reg)     S (reg)`
  - `MVW    T (reg)     D (imm8)`
- Byte order:
  - `00000SSS 00000TTT`
  - `00001TTT DDDDDDDD`
- Function:
  - `GPR[S] -> GPR[T]`
  - `D -> GPR[T]`

## STW - Store word

- Description:
- Assembly:
  - `STW    S (reg)`
  - `STW    A (imm16)   S (reg)`
- Byte order:
  - `00010SSS`
  - `00011SSS AAAAAAAA AAAAAAAA`
- Function:
  - `GPR[S] -> RAM[GH]`
  - `GPR[S] -> RAM[A]`

## LDW - Load word

- Description:
- Assembly:
  - `LDW    S (reg)`
  - `LDW    A (imm16)   S (reg)`
- Byte order:
  - `00100SSS`
  - `00101SSS AAAAAAAA AAAAAAAA`
- Function:
  - `RAM[GH] -> GPR[S]`
  - `RAM[A} -> GPR[S]`

## PSH - Stack push

- Description:
- Assembly:
  - `PSH    S (reg)`
  - `PSH    D (imm8)`
- Byte order:
  - `00110SSS`
  - `00111xxx DDDDDDDD`
- Function:
  - `GPR[S] -> RAM[SP++]`
  - `D -> RAM[SP++]`

## POP - Stack pop

- Description:
- Assembly:
  - `POP    S (reg)`
  - `POP    S (reg)`
- Byte order:
  - `01000SSS`
  - `01001SSS`
- Function:
  - `RAM[--SP] -> GPR[S]`
  - `RAM[--SP] -> GPR[S]`

## PIN - Port in

- Description:
- Assembly:
  - `PIN    T (reg)     S (reg)`
  - `PIN    T (reg)     D (imm8)`
- Byte order:
  - `01010SSS 01010TTT`
  - `01011TTT DDDDDDDD`
- Function:
  - `PORT[S] -> GPR[T]`
  - `PORT[D] -> GPR[T]`

## PUT - Port out

- Description:
- Assembly:
- Byte order:
- Function:

## JNZ - Jump if not zero

- Description:
- Assembly:
- Byte order:
- Function:

## HNZ - Halt if not zero

- Description:
- Assembly:
- Byte order:
- Function:

## CMP - Compare words

- Description:
- Assembly:
- Byte order:
- Function:

## AND - Bitwise AND

- Description:
- Assembly:
- Byte order:
- Function:

## ORR - Bitwise OR

- Description:
- Assembly:
- Byte order:
- Function:

## NOR - Bitwise NOR

- Description:
- Assembly:
- Byte order:
- Function:

## SFT - Right shift

- Description:
- Assembly:
- Byte order:
- Function:

## ADC - Add with carry

- Description:
- Assembly:
- Byte order:
- Function:

## SBB - Subtract with borrow

- Description:
- Assembly:
- Byte order:
- Function:

