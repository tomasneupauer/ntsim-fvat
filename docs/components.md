# Components

## And
- Inputs:
A - Input byte A
B - Input byte B
- Outputs:
AND - Result byte
- Function:
A & B -> AND

## Or
- Inputs:
A - Input byte A
B - Input byte B
- Outputs:
OR - Result byte
- Function:
A | B -> OR

## Nor
- Inputs:
A - Input byte A
B - Input byte B
- Outputs:
NOR - Result byte
- Function:
~( A | B ) -> NOR

## RightShift
- Inputs:
A - Input byte
i - Carry in
- Outputs:
SFT - Result byte
o - Carry out
- Function:
( A >> 1 ) | ( i << 7 ) -> SFT
A & 1 -> o

## Or
- Inputs:
- Outputs:
- Function:

## Or
- Inputs:
- Outputs:
- Function:
