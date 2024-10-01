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

|           | 000 | `              ` | `00000xxx` | `00000xxx` |
