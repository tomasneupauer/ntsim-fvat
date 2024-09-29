# Components

## BitAnd
- Description:
  - Performs bitwise AND on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - AND - Result byte
- Function:
  - `A & B -> AND`

## BitOr
- Description:
  - Performs bitwise OR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - OR - Result byte
- Function:
  - `A | B -> OR`

## BitNor
- Description:
  - Performs bitwise NOR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - NOR - Result byte
- Function:
  - `~( A | B ) -> NOR`

## RightShift 
- Description:
  - Shifts given byte to the right
  - MSB is set to Carry in
  - LSB is sent to Carry out
- Inputs:
  - A - Input byte
  - i - Carry in
- Outputs:
  - SFT - Result byte
  - o - Carry out
- Function:
  - `( A >> 1 ) | ( i << 7 ) -> SFT`
  - `A & 1 -> o`

## Decoder
- Description:
  - Decodes 3-bit code to 8 signals
- Inputs:
  - C - Input 3-bit code
  - E - Enable control
- Outputs:
  - D - Decoded signals
- Function:
  - `2 ** C - > D`

## HalfAdder
- Description:
  - Adds Carry in to given byte
  - Overflow is sent to Carry out
- Inputs:
  - A - Input byte
  - i - Carry in
- Outputs:
  - S - Result byte
  - o - Carry out
- Function:
  - `A + i -> S`
  - `( A + i ) > 255 -> o`

## IncDec
- Description:
  - Increments or decrements given byte
  - Overflow is sent to Carry out
- Inputs:
  - A - Input byte
  - M - Mode control (0-Inc 1-Dec)
- Outputs:
  - S - Result byte
  - o - Carry out
- Function:
  - `M == 0 && A + 1 -> S`
  - `M == 1 && A - 1 -> S`
  - `( A + 1 ) > 255 | ( A - 1 ) < 0 - > o`

## AdcSbb
- Description:
- Inputs:
- Outputs:
- Function:

## Comparator
- Description:
- Inputs:
- Outputs:
- Function:

## D-Latch
- Description:
- Inputs:
- Outputs:
- Function:

## D-FlipFlop
- Description:
- Inputs:
- Outputs:
- Function:

