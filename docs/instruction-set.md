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
  - `LDW    T (reg)`
  - `LDW    A (imm16)   T (reg)`
- Byte order:
  - `00100TTT`
  - `00101TTT AAAAAAAA AAAAAAAA`
- Function:
  - `RAM[GH] -> GPR[T]`
  - `RAM[A} -> GPR[T]`

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
  - `POP    T (reg)`
  - `POP    T (reg)`
- Byte order:
  - `01000TTT`
  - `01001TTT`
- Function:
  - `RAM[--SP] -> GPR[T]`
  - `RAM[--SP] -> GPR[T]`

## PIN - Port in

- Description:
- Assembly:
  - `PIN    T (reg)     S (reg)`
  - `PIN    T (reg)     D (imm8)`
- Byte order:
  - `01010SSS 01010TTT`
  - `01011TTT DDDDDDDD`
- Function:
  - `DEV[S] -> GPR[T]`
  - `DEV[D] -> GPR[T]`

## PUT - Port out

- Description:
- Assembly:
  - `PUT    S (reg)     T (reg)`
  - `PUT    S (reg)     D (imm8)`
- Byte order:
  - `01100TTT 01100SSS`
  - `01101SSS DDDDDDDD`
- Function:
  - `GPR[S] -> DEV[T]`
  - `GPR[S] -> DEV[D]`

## JNZ - Jump if not zero

- Description:
- Assembly:
  - `JNZ    S (reg)`
  - `JNZ    D (imm8)`
- Byte order:
  - `01110SSS`
  - `01111xxx DDDDDDDD`
- Function:
  - `( GPR[S] != 0 ) ? GH -> PC`
  - `( D != 0 ) ? GH -> PC`

## HNZ - Halt if not zero

- Description:
- Assembly:
  - `HNZ    S (reg)`
  - `HNZ    D (imm8)`
- Byte order:
  - `10000SSS`
  - `10001xxx DDDDDDDD`
- Function:
  - `( GPR[S] != 0 ) -> HLT`
  - `( D != 0 ) -> HLT`

## CMP - Compare words

- Description:
  - Performs a comparsion on a pair of words
- Assembly:
  - `CMP    T (reg)     S (reg)`
  - `CMP    T (reg)     D (imm8)`
- Byte order:
  - `10010SSS 10010TTT`
  - `10011TTT DDDDDDDD`
- Function:
  - `( GPR[S] > GPR[T] ) -> g @ ( GPR[S] < GPR[T] ) -> l @ ( GPR[S] == GPR[T] ) -> e`
  - `( GPR[T] > D ) -> g @ ( GPR[T] < D ) -> l @ ( GPR[T] == D ) -> e`
  - `( e << 3 ) & ( l << 2 ) & ( g << 1 ) & o -> GPR[F]`

## AND - Bitwise AND

- Description:
  - Performs a bitwise AND on a pair of words
- Assembly:
  - `AND    T (reg)     S (reg)`
  - `AND    T (reg)     D (imm8)`
- Byte order:
  - `10100SSS 10100TTT`
  - `10101TTT DDDDDDDD`
- Function:
  - `GPR[T] & GPR[S] -> GPR[T]`
  - `GPR[T] & D -> GPR[T]`

## ORR - Bitwise OR

- Description:
  - Performs a bitwise OR on a pair of words
- Assembly:
  - `ORR    T (reg)     S (reg)`
  - `ORR    T (reg)     D (imm8)`
- Byte order:
  - `10110SSS 10110TTT`
  - `10111TTT DDDDDDDD`
- Function:
  - `GPR[T] | GPR[S] -> GPR[T]`
  - `GPR[T] | D -> GPR[T]`

## NOR - Bitwise NOR

- Description:
  - Performs a bitwise NOR on a pair of words
- Assembly:
  - `NOR    T (reg)     S (reg)`
  - `NOR    T (reg)     D (imm8)`
- Byte order:
  - `11000SSS 11000TTT`
  - `11001TTT DDDDDDDD`
- Function:
  - `~( GPR[T] | GPR[S] ) -> GPR[T]`
  - `~( GPR[T] | D ) -> GPR[T]`

## SFR - Right shift

- Description:
  - Performs a right shift on a given word
- Assembly:
  - `AND    T (reg)     S (reg)`
  - `AND    T (reg)     D (imm8)`
- Byte order:
  - `11010SSS 11010TTT`
  - `11011TTT DDDDDDDD`
- Function:
  - `( GPR[S] >> 1 ) & ( i << 7 ) -> GPR[T]`
  - `( D >> 1 ) & ( i << 7 ) -> GPR[T]`

## ADC - Add with carry

- Description:
  - Performs an addition with carry on a pair of words
- Assembly:
  - `ADC    T (reg)     S (reg)`
  - `ADC    T (reg)     D (imm8)`
- Byte order:
  - `11100SSS 11100TTT`
  - `11101TTT DDDDDDDD`
- Function:
  - `GPR[T] + GPR[S] + i -> GPR[T]`
  - `GPR[T] + D + i -> GPR[T]`

## SBB - Subtract with borrow

- Description:
  - Performs a subtraction with borrow on a pair of words
- Assembly:
  - `SBB    T (reg)     S (reg)`
  - `SBB    T (reg)     D (imm8)`
- Byte order:
  - `11110SSS 11110TTT`
  - `11111TTT DDDDDDDD`
- Function:
  - `GPR[T] - GPR[S] + i -> GPR[T]`
  - `GPR[T] - D + i -> GPR[T]`

