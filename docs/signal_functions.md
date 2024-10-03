# Signal Functions

Microcode signals in logic function representation.
Symbols A-E are five most significant bits of current instruction.
Symbols F-H are three least significant bits of curren step.
Symbol T is used in conditional instructions. T is set if byte on data bus is not zero.

## Logic functions

- *[ABCDEFGH]* = `IR & 0xf8 | SC & 0x07`
- **T** = `DATA != 0`

- **LR** = `(~A & ~C & ~D & ~E & F & ~G & ~H) | (~A & ~B & ~C & ~D & E & ~F & G & H) | (~A & ~B & ~C & D & ~E & ~F & G & H) | (~A & ~B & ~C & D & E & F & G & H) | (~A & B & ~C & F & ~G & ~H) | (A & C & ~E & F & ~G & H) | (A & C & E & F & ~G & ~H) | (A & B & ~E & F & ~G & H) | (B & ~C & E & F & ~G & ~H)`
- **LF** = `(A & ~B & ~C & D & ~E & F & ~G & H) | (A & ~B & ~C & D & E & F & ~G & ~H) | (A & C & ~E & F & G & ~H) | (A & C & E & F & ~G & H) | (A & B & ~E & F & G & ~H) | (A & B & E & F & ~G & H)`
- **LG** = `(~A & ~B & ~C & D & E & ~F & G & H) | (~A & ~B & C & ~D & E & ~F & G & H)`
- **LH** = `(~A & ~B & ~C & D & E & F & ~G & H) | (~A & ~B & C & ~D & E & F & ~G & H)`
- **ER** = `(~B & ~C & ~D & ~E & ~F & G & ~H) | (~A & ~B & C & ~E & ~F & G & H) | (~A & ~B & C & ~D & E & F & G & H) | (B & D & ~E & ~F & G & ~H) | (B & C & ~E & ~F & G & ~H) | (~A & B & C & ~D & F & ~G & ~H) | (A & D & ~E & F & ~G & ~H) | (A & D & ~F & G & ~H) | (A & C & ~E & F & ~G & ~H) | (A & C & ~F & G & ~H) | (A & B & ~E & F & ~G & ~H) | (A & B & ~F & G & ~H)`
- **AR** = `(~A & ~B & ~C & D & ~E & ~F & G & ~H) | (~A & ~B & ~C & D & E & F & G & ~H) | (~A & ~B & C & ~D & ~E & ~F & G & ~H) | (~A & ~B & C & ~D & E & F & G & ~H) | (~A & B & C & D & ~E & ~F & G & ~H & T) | (~A & B & C & D & E & ~F & G & H & T)`
- **LX** = `(~A & ~B & ~C & ~D & ~E & ~F & G & ~H) | (~A & ~B & C & D & E & ~F & G & H) | (A & D & ~F & G & ~H) | (A & C & ~F & G & ~H) | (A & B & ~F & G & ~H)`
- **LY** = `(A & D & ~E & F & ~G & ~H) | (A & D & E & ~F & G & H) | (A & C & ~E & F & ~G & ~H) | (A & C & E & ~F & G & H) | (A & B & ~E & F & ~G & ~H) | (A & B & E & ~F & G & H)`
- **EZ** = `(~A & ~B & ~C & ~D & ~E & F & ~G & ~H) | (~A & ~B & C & D & E & F & ~G & H) | (A & C & ~E & F & ~G & H) | (A & C & E & F & ~G & ~H) | (A & B & ~E & F & ~G & H) | (A & B & E & F & ~G & ~H)`
- **EF** = `(A & ~B & ~C & D & ~E & F & ~G & H) | (A & ~B & ~C & D & E & F & ~G & ~H) | (A & C & ~E & F & G & ~H) | (A & C & E & F & ~G & H) | (A & B & ~E & F & G & ~H) | (A & B & E & F & ~G & H)`
- **IC** = `(~A & ~B & ~C & ~D & ~F & H) | (~F & ~G & H) | (~A & ~B & ~C & D & E & ~G & H) | (~A & ~B & C & ~D & E & ~G & H) | (B & ~C & D & ~F & H) | (B & C & ~D & ~F & H) | (A & D & ~F & H) | (A & C & ~F & H) | (A & B & ~F & H) | (~A & ~B & E & ~F & H) | (D & E & ~F & H)`
- **AC** = `(~A & ~C & ~D & ~F & ~H) | (~F & ~G & ~H) | (E & ~F & ~H) | (~A & ~B & ~C & D & E & ~G & ~H) | (~A & ~B & C & ~D & E & ~G & ~H) | (B & ~C & ~F & ~H) | (B & ~D & ~F & ~H) | (A & D & ~F & ~H) | (A & C & ~F & ~H)`
- **IS** = `(~A & ~B & C & D & ~E & ~F & G & H) | (~A & ~B & C & D & E & F & ~G & H)`
- **DS** = `(~A & B & ~C & ~D & ~F & G & ~H)`
- **AS** = `(~A & ~B & C & D & ~E & ~F & G & ~H) | (~A & ~B & C & D & E & F & ~G & ~H) | (~A & B & ~C & ~D & ~F & G & H)`
- **RI** = `(~A & ~B & C & ~E & ~F & G & H) | (~A & ~B & C & ~D & E & F & G & H) | (~A & ~B & C & D & E & F & ~G & H)`
- **RO** = `(~A & ~B & ~C & D & ~E & ~F & G & H) | (~A & ~B & ~C & D & E & F & G & H) | (~A & B & ~C & ~D & F & ~G & ~H)`
- **MO** = `(~A & ~B & ~C & ~D & ~F & H) | (~F & ~G & H) | (~A & ~B & ~C & D & E & ~G & H) | (~A & ~B & C & ~D & E & ~G & H) | (B & ~C & D & ~F & H) | (B & C & ~D & ~F & H) | (A & D & ~F & H) | (A & C & ~F & H) | (A & B & ~F & H) | (~B & E & ~F & H) | (D & E & ~F & H)`
- **PI** = `(~A & B & C & ~D & F & ~G & ~H)`
- **PO** = `(~A & B & ~C & D & F & ~G & ~H)`
- **LI** = `(~A & ~B & ~C & ~D & ~E & ~F & H) | (~F & ~G & H) | (B & ~C & D & ~E & ~F & H) | (B & C & ~D & ~E & ~F & H) | (A & D & ~E & ~F & H) | (A & C & ~E & ~F & H) | (A & B & ~E & ~F & H)`
- **LM** = `(~A & ~B & ~C & D & E & ~H) | (~A & ~B & C & ~D & E & ~H) | (~A & B & ~C & ~D & ~F & G) | (~F & ~G & ~H) | (E & ~F & ~H) | (~A & ~B & ~F & ~H) | (~A & ~B & D & E & ~G & ~H) | (~C & D & ~F & ~H) | (B & ~D & ~F & ~H) | (A & C & ~F & ~H)`
- **XT** = `(~A & ~C & ~D & ~E & F & ~G & ~H) | (~B & ~C & ~D & E & ~F & G & H) | (~A & ~B & D & ~E & ~F & G & H) | (~A & ~B & ~C & D & E & F & G & H) | (~A & ~B & C & ~E & ~F & G & H) | (~A & ~B & C & ~D & E & F & G & H) | (~B & C & D & E & F & ~G & H) | (~A & B & ~C & F & ~G & ~H) | (~A & B & ~D & F & ~G & ~H) | (~A & B & C & D & ~E & ~F & G & ~H) | (~A & B & C & D & E & ~F & G & H) | (A & ~B & ~C & ~D & ~E & ~F & G & ~H) | (A & ~B & ~C & D & ~E & F & ~G & H) | (A & ~B & ~C & D & E & F & ~G & ~H) | (A & C & ~E & F & G & ~H) | (A & C & E & F & ~G & H) | (A & B & ~E & F & G & ~H) | (A & B & E & F & ~G & H)`
- **LP** = `(~A & B & ~C & D & ~E & ~F & G & ~H) | (~A & B & ~C & D & E & ~F & G & H) | (~A & B & C & ~D & ~E & ~F & G & ~H) | (~A & B & C & ~D & E & ~F & G & H)`
- **RC** = `(~A & B & C & D & ~E & ~F & G & ~H & T) | (~A & B & C & D & E & ~F & G & H & T)`
- **HF** = `(A & ~B & ~C & ~D & ~E & ~F & G & ~H & T) | (A & ~B & ~C & ~D & E & ~F & G & H & T)`

