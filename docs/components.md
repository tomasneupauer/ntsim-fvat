# Components

## And
- Description:
  - Performs bitwise AND on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - AND - Result byte
- Function:
  - A & B -> AND

## Or
- Description:
  - Performs bitwise OR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - OR - Result byte
- Function:
  - A | B -> OR

## Nor
- Description:
  - Performs bitwise NOR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - NOR - Result byte
- Function:
  - ~( A | B ) -> NOR

## RightShift 
- Description:
  - Shifts given byte to the right
  - MSB is set to Carry in (i)
  - LSB is sent to Carry out (o)
- Inputs:
  - A - Input byte
  - i - Carry in
- Outputs:
  - SFT - Result byte
  - o - Carry out
- Function:
  - ( A >> 1 ) | ( i << 7 ) -> SFT
  - A & 1 -> o

## Decoder
- Description:
  - Decodes 3-bit code to 8 signals
- Inputs:
  - C - Input 3-bit code
  - E - Enable control
- Outputs:
  - D - Decoded signals
- Function:
  - 2 ** C - > D

## Or
- Description:
- Inputs:
- Outputs:
- Function:
