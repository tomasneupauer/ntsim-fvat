# Instruction Set

## MVW - Move word

- Description:
  - Moves word to register A from register B or imm8
- Assembly:
  - `MVW     T-reg   S-reg   `
  - `MVW     T-reg   D-imm8  `
- Byte order:
  - `00000SSS 00000TTT`
  - `00001TTT DDDDDDDD`
- Function:
  - `GPR(S) -> GPR(T)`
  - `D-imm8 -> GPR(T)`

## STW - Store word

## LDW - Load word

## PSH - Stack push

## POP - Stack pop

## PIN - Port in

## PUT - Port out

## JNZ - Jump if not zero

## HNZ - Halt if not zero

## CMP - Compare words

## AND - Bitwise AND

## ORR - Bitwise OR

## NOR - Bitwise NOR

## SFT - Right shift

## ADC - Add with carry

## SBB - Subtract with borrow
