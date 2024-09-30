# Components

- [BitAnd](#bitand)
- [BitOr](#bitor)
- [BitNor](#bitnor)
- [RightShift](#rightshift)
- [Decoder](#decoder)
- [HalfAdder](#halfadder)
- [IncDec](incdec)
- [AdcSbb](adcsbb)
- [Comparator](comparator)
- [D-Latch](d-latch)
- [D-FlipFlop](d-flipflop)

## BitAnd

- Description:
  - Performs a bitwise AND on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - AND - Result byte
- Function:
  - `A & B -> AND`

## BitOr

- Description:
  - Performs a bitwise OR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - OR - Result byte
- Function:
  - `A | B -> OR`

## BitNor

- Description:
  - Performs a bitwise NOR on a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - NOR - Result byte
- Function:
  - `~( A | B ) -> NOR`

## RightShift 
- Description:
  - Shifts a given byte to the right
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
  - Decodes a 3-bit code to an 8-bit signal
- Inputs:
  - C - Input 3-bit code
  - E - Enable control
- Outputs:
  - D - Decoded 8-bit signal
- Function:
  - `2 ** C -> D`

## HalfAdder
- Description:
  - Adds Carry in to a given byte
  - Overflow is sent to Carry out
- Inputs:
  - A - Input byte
  - i - Carry in
- Outputs:
  - S - Result byte
  - o - Carry out
- Function:
  - `A + i -> S`
  - `S > 255 -> o`

## IncDec
- Description:
  - Increments or decrements a given byte
  - Overflow is sent to Carry out
- Inputs:
  - A - Input byte
  - M - Mode control ( 0-Inc 1-Dec )
- Outputs:
  - S - Result byte
  - o - Carry out
- Function:
  - `~M ? ( A + 1 ) : ( A - 1 ) -> S`
  - `~M ? ( S > 255 ) : ( S < 0 ) -> o`

## AdcSbb
- Description:
  - Adds a pair of bytes with carry
  - Subtracts a pair of bytes with borrow
  - Carry or borrow is sent to Carry out
- Inputs:
  - A - Input byte A
  - B - Input byte B
  - M - Mode control ( 0-Adc 1-Sbb )
  - i - Carry in
- Outputs:
  - S - Result byte
  - o - Carry out
- Function:
  - `~M ? ( A + B + i ) : ( A - B + i ) -> S`
  - `~M ? ( S > 255 ) : ~( S < 0 ) -> o`

## Comparator
- Description:
  - Compares a pair of bytes
- Inputs:
  - A - Input byte A
  - B - Input byte B
- Outputs:
  - A\>B - A is greater than B
  - A\<B - A is less than B
  - A=B - A is equal to B
- Function:
  - `A > B -> A>B`
  - `A < B -> A<B`
  - `A == B -> A=B`

## D-Latch
- Description:
  - Stores a given byte
  - Byte is fixed when Enable is low
- Inputs:
  - D - Input byte
  - E - Enable control
  - R - Reset control
- Outputs:
  - Q - Stored byte
- Function:
  - `E ? D : Q -> Q`

## D-FlipFlop
- Description:
  - Stores a given byte
  - Byte is stored on Clock rising edge
- Inputs:
  - D - Input byte
  - C - Clock control
  - R - Reset control
- Outputs:
  - Q - Stored byte
- Function:
  - `C ? D : Q -> Q`

