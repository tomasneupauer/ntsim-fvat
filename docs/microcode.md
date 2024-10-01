# Microcode

| Instruction | Step | Signals | Inst Reg | Memory |
| :---------: | :--: | :------ | :------: | :----: |
| **MVW-R** | 000 | `AC LM         ` | `xxxxxxxx` | `00000aaa` |
|           | 001 | `MO LI IC      ` | `00000aaa` | `00000aaa` |
|           | 010 | `AC LM ER LX   ` | `00000aaa` | `00000bbb` |
|           | 011 | `MO LI IC      ` | `00000bbb` | `00000bbb` |
|           | 100 | `EZ LR XT      ` | `00000bbb` | `00000bbb` |
| **MVW-I** | 000 | `AC LM         ` | `xxxxxxxx` | `00001aaa` |
|           | 001 | `MO LI IC      ` | `00001aaa` | `00001aaa` |
|           | 010 | `AC LM         ` | `00001aaa` | `DDDDDDDD` |
|           | 011 | `MO LR IC XT   ` | `00001aaa` | `DDDDDDDD` |
| **LDW-R** | 000 | `AC LM         ` | `xxxxxxxx` | `00010aaa` |
|           | 001 | `MO LI IC      ` | `00010aaa` | `00010aaa` |
|           | 010 | `AR LM         ` | `00010aaa` | `RAM-[GH]` |
|           | 011 | `RO LR XT      ` | `00010aaa` | `RAM-[GH]` |
| **LDW-I** | 000 | `AC LM         ` | `xxxxxxxx` | `00011aaa` |
|           | 001 | `MO LI IC      ` | `00011aaa` | `00011aaa` |
|           | 010 | `AC LM         ` | `00011aaa` | `GGGGGGGG` |
|           | 011 | `MO LG IC      ` | `00011aaa` | `GGGGGGGG` |
|           | 100 | `AC LM         ` | `00011aaa` | `HHHHHHHH` |
|           | 101 | `MO LH IC      ` | `00011aaa` | `HHHHHHHH` |
|           | 110 | `AR LM         ` | `00011aaa` | `RAM-[GH]` |
|           | 111 | `RO LR XT      ` | `00011aaa` | `RAM-[GH]` |
| **STW-R** | 000 | `AC LM         ` | `xxxxxxxx` | `00100aaa` |
|           | 001 | `MO LI IC      ` | `00100aaa` | `00100aaa` |
|           | 010 | `AR LM         ` | `00100aaa` | `RAM-[GH]` |
|           | 011 | `ER RI XT      ` | `00100aaa` | `RAM-[GH]` |
| **STW-I** | 000 | `AC LM         ` | `xxxxxxxx` | `00101aaa` |
|           | 001 | `MO LI IC      ` | `00101aaa` | `00101aaa` |
|           | 010 | `AC LM         ` | `00101aaa` | `GGGGGGGG` |
|           | 011 | `MO LG IC      ` | `00101aaa` | `GGGGGGGG` |
|           | 100 | `AC LM         ` | `00101aaa` | `HHHHHHHH` |
|           | 101 | `MO LH IC      ` | `00101aaa` | `HHHHHHHH` |
|           | 110 | `AR LM         ` | `00101aaa` | `RAM-[GH]` |
|           | 111 | `ER RI XT      ` | `00101aaa` | `RAM-[GH]` |
| **PSH-R** | 000 | `AC LM         ` | `xxxxxxxx` | `00110aaa` |
|           | 001 | `MO LI IC      ` | `00110aaa` | `00110aaa` |
|           | 010 | `AS LM         ` | `00110aaa` | `STK-[SP]` |
|           | 011 | `ER RI IS XT   ` | `00110aaa` | `STK-[SP]` |
| **PSH-I** | 000 | `AC LM         ` | `xxxxxxxx` | `00111xxx` |
|           | 001 | `MO LI IC      ` | `00111xxx` | `00111xxx` |
|           | 010 | `AC LM         ` | `00111xxx` | `DDDDDDDD` |
|           | 011 | `MO LX IC      ` | `00111xxx` | `DDDDDDDD` |
|           | 100 | `AS LM         ` | `00111xxx` | `STK-[SP]` |
|           | 101 | `EZ RI IS XT   ` | `00111xxx` | `STK-[SP]` |
| **POP-R** | 000 | `AC LM         ` | `xxxxxxxx` | `01000aaa` |
|           | 001 | `MO LI IC      ` | `01000aaa` | `01000aaa` |
|           | 010 | `AC LM DS      ` | `01000aaa` | `01000aaa` |
|           | 011 | `AS LM         ` | `01000aaa` | `STK-[SP]` |
|           | 100 | `RO LR XT      ` | `01000aaa` | `STK-[SP]` |
| **POP-I** | 000 | `AC LM         ` | `xxxxxxxx` | `01001aaa` |
|           | 001 | `MO LI IC      ` | `01001aaa` | `01001aaa` |
|           | 010 | `AC LM DS      ` | `01001aaa` | `01001aaa` |
|           | 011 | `AS LM         ` | `01001aaa` | `STK-[SP]` |
|           | 100 | `RO LR XT      ` | `01001aaa` | `STK-[SP]` |
| **INB-R** | 000 | `AC LM         ` | `xxxxxxxx` | `01010aaa` |
|           | 001 | `MO LI IC      ` | `01010aaa` | `01010aaa` |
|           | 010 | `AC LM ER LP   ` | `01010aaa` | `01010bbb` |
|           | 011 | `MO LI IC      ` | `01010bbb` | `01010bbb` |
|           | 100 | `PO LR XT      ` | `01010bbb` | `01010bbb` |
| **INB-I** | 000 | `AC LM         ` | `xxxxxxxx` | `01011aaa` |
|           | 001 | `MO LI IC      ` | `01011aaa` | `01011aaa` |
|           | 010 | `AC LM         ` | `01011aaa` | `DDDDDDDD` |
|           | 011 | `MO LP IC      ` | `01011aaa` | `DDDDDDDD` |
|           | 100 | `PO LR XT      ` | `01011aaa` | `DDDDDDDD` |
| **OUB-R** | 000 | `AC LM         ` | `xxxxxxxx` | `01100aaa` |
|           | 001 | `MO LI IC      ` | `01100aaa` | `01100aaa` |
|           | 010 | `AC LM ER LP   ` | `01100aaa` | `01100bbb` |
|           | 011 | `MO LI IC      ` | `01100bbb` | `01100bbb` |
|           | 100 | `ER PI XT      ` | `01100bbb` | `01100bbb` |
| **OUB-I** | 000 | `AC LM         ` | `xxxxxxxx` | `01101aaa` |
|           | 001 | `MO LI IC      ` | `01101aaa` | `01101aaa` |
|           | 010 | `AC LM         ` | `01101aaa` | `DDDDDDDD` |
|           | 011 | `MO LP IC      ` | `01101aaa` | `DDDDDDDD` |
|           | 100 | `ER PI XT      ` | `01101aaa` | `DDDDDDDD` |
| **JNZ-R** | 000 | `AC LM         ` | `xxxxxxxx` | `01110aaa` |
|           | 001 | `MO LI IC      ` | `01110aaa` | `01110aaa` |
| *True*    | 010 | `ER AR RC XT   ` | `01110aaa` | `01110aaa` |
| *False*   | 010 | `ER AC LM XT   ` | `01110aaa` | `01110aaa` |
| **JNZ-I** | 000 | `AC LM         ` | `xxxxxxxx` | `01111xxx` |
|           | 001 | `MO LI IC      ` | `01111xxx` | `01111xxx` |
|           | 010 | `AC LM         ` | `01111xxx` | `DDDDDDDD` |
| *True*    | 011 | `MO AR RC IC XT` | `01111xxx` | `DDDDDDDD` |
| *False*   | 011 | `MO IC XT      ` | `01111xxx` | `DDDDDDDD` |
| **HNZ-R** | 000 | `AC LM         ` | `xxxxxxxx` | `10000aaa` |
|           | 001 | `MO LI IC      ` | `10000aaa` | `10000aaa` |
| *True*    | 010 | `ER AC LM HF XT` | `10000aaa` | `10000aaa` |
| *False*   | 010 | `ER AC LM XT   ` | `10000aaa` | `10000aaa` |
| **HNZ-I** | 000 | `AC LM         ` | `xxxxxxxx` | `10001xxx` |
|           | 001 | `MO LI IC      ` | `10001xxx` | `10001xxx` |
|           | 010 | `AC LM         ` | `10001xxx` | `DDDDDDDD` |
| *True*    | 011 | `MO HF IC XT   ` | `10001xxx` | `DDDDDDDD` |
| *False*   | 011 | `MO IC XT      ` | `10001xxx` | `DDDDDDDD` |
| **CMP-R** | 000 | `AC LM         ` | `xxxxxxxx` | `10001xxx` |
|           | 001 | `MO LI IC      ` | `10010aaa` | `10001xxx` |
|           | 010 | `AC LM ER LX   ` | `10010aaa` | `00000xxx` |
|           | 011 | `MO LI IC      ` | `10010bbb` | `00000xxx` |
|           | 100 | `ER LY         ` | `10010bbb` | `00000xxx` |
|           | 101 | `EF LF XT      ` | `10010bbb` | `00000xxx` |
| **CMP-I** | 000 | `AC LM         ` | `xxxxxxxx` | `10011aaa` |
|           | 001 | `MO LI IC      ` | `10011aaa` | `10011aaa` |
|           | 010 | `AC LM ER LX   ` | `10011aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `10011aaa` | `DDDDDDDD` |
|           | 100 | `EF LF XT      ` | `10011aaa` | `DDDDDDDD` |
| **AND-R** | 000 | `AC LM         ` | `xxxxxxxx` | `10100aaa` |
|           | 001 | `MO LI IC      ` | `10100aaa` | `10100aaa` |
|           | 010 | `AC LM ER LX   ` | `10100aaa` | `10100bbb` |
|           | 011 | `MO LI IC      ` | `10100bbb` | `10100bbb` |
|           | 100 | `ER LY         ` | `10100bbb` | `10100bbb` |
|           | 101 | `EZ LR         ` | `10100bbb` | `10100bbb` |
|           | 110 | `EF LF XT      ` | `10100bbb` | `10100bbb` |
| **AND-I** | 000 | `AC LM         ` | `xxxxxxxx` | `10101aaa` |
|           | 001 | `MO LI IC      ` | `10101aaa` | `10101aaa` |
|           | 010 | `AC LM ER LX   ` | `10101aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `10101aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `10101aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `10101aaa` | `DDDDDDDD` |
| **ORR-R** | 000 | `AC LM         ` | `xxxxxxxx` | `10110aaa` |
|           | 001 | `MO LI IC      ` | `10110aaa` | `10110aaa` |
|           | 010 | `AC LM ER LX   ` | `10110aaa` | `10110bbb` |
|           | 011 | `MO LI IC      ` | `10110bbb` | `10110bbb` |
|           | 100 | `ER LY         ` | `10110bbb` | `10110bbb` |
|           | 101 | `EZ LR         ` | `10110bbb` | `10110bbb` |
|           | 110 | `EF LF XT      ` | `10110bbb` | `10110bbb` |
| **ORR-I** | 000 | `AC LM         ` | `xxxxxxxx` | `10111aaa` |
|           | 001 | `MO LI IC      ` | `10111aaa` | `10111aaa` |
|           | 010 | `AC LM ER LX   ` | `10111aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `10111aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `10111aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `10111aaa` | `DDDDDDDD` |
| **NOR-R** | 000 | `AC LM         ` | `xxxxxxxx` | `11000aaa` |
|           | 001 | `MO LI IC      ` | `11000aaa` | `11000aaa` |
|           | 010 | `AC LM ER LX   ` | `11000aaa` | `11000bbb` |
|           | 011 | `MO LI IC      ` | `11000bbb` | `11000bbb` |
|           | 100 | `ER LY         ` | `11000bbb` | `11000bbb` |
|           | 101 | `EZ LR         ` | `11000bbb` | `11000bbb` |
|           | 110 | `EF LF XT      ` | `11000bbb` | `11000bbb` |
| **NOR-I** | 000 | `AC LM         ` | `xxxxxxxx` | `11001aaa` |
|           | 001 | `MO LI IC      ` | `11001aaa` | `11001aaa` |
|           | 010 | `AC LM ER LX   ` | `11001aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `11001aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `11001aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `11001aaa` | `DDDDDDDD` |
| **SFR-R** | 000 | `AC LM         ` | `xxxxxxxx` | `11010aaa` |
|           | 001 | `MO LI IC      ` | `11010aaa` | `11010aaa` |
|           | 010 | `AC LM ER LX   ` | `11010aaa` | `11010bbb` |
|           | 011 | `MO LI IC      ` | `11010bbb` | `11010bbb` |
|           | 100 | `ER LY         ` | `11010bbb` | `11010bbb` |
|           | 101 | `EZ LR         ` | `11010bbb` | `11010bbb` |
|           | 110 | `EF LF XT      ` | `11010bbb` | `11010bbb` |
| **SFR-I** | 000 | `AC LM         ` | `xxxxxxxx` | `11011aaa` |
|           | 001 | `MO LI IC      ` | `11011aaa` | `11011aaa` |
|           | 010 | `AC LM ER LX   ` | `11011aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `11011aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `11011aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `11011aaa` | `DDDDDDDD` |
| **ADC-R** | 000 | `AC LM         ` | `xxxxxxxx` | `11100aaa` |
|           | 001 | `MO LI IC      ` | `11100aaa` | `11100aaa` |
|           | 010 | `AC LM ER LX   ` | `11100aaa` | `11100bbb` |
|           | 011 | `MO LI IC      ` | `11100bbb` | `11100bbb` |
|           | 100 | `ER LY         ` | `11100bbb` | `11100bbb` |
|           | 101 | `EZ LR         ` | `11100bbb` | `11100bbb` |
|           | 110 | `EF LF XT      ` | `11100bbb` | `11100bbb` |
| **ADC-I** | 000 | `AC LM         ` | `xxxxxxxx` | `11101aaa` |
|           | 001 | `MO LI IC      ` | `11101aaa` | `11101aaa` |
|           | 010 | `AC LM ER LX   ` | `11101aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `11101aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `11101aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `11101aaa` | `DDDDDDDD` |
| **SBB-R** | 000 | `AC LM         ` | `xxxxxxxx` | `11110aaa` |
|           | 001 | `MO LI IC      ` | `11110aaa` | `11110aaa` |
|           | 010 | `AC LM ER LX   ` | `11110aaa` | `11110bbb` |
|           | 011 | `MO LI IC      ` | `11110bbb` | `11110bbb` |
|           | 100 | `ER LY         ` | `11110bbb` | `11110bbb` |
|           | 101 | `EZ LR         ` | `11110bbb` | `11110bbb` |
|           | 110 | `EF LF XT      ` | `11110bbb` | `11110bbb` |
| **SBB-I** | 000 | `AC LM         ` | `xxxxxxxx` | `11111aaa` |
|           | 001 | `MO LI IC      ` | `11101aaa` | `11111aaa` |
|           | 010 | `AC LM ER LX   ` | `11111aaa` | `DDDDDDDD` |
|           | 011 | `MO LY IC      ` | `11111aaa` | `DDDDDDDD` |
|           | 100 | `EZ LR         ` | `11111aaa` | `DDDDDDDD` |
|           | 101 | `EF LF XT      ` | `11111aaa` | `DDDDDDDD` |

