all: simulator assembler

simulator: src/ntsim.cpp
	g++ src/ntsim.cpp -o build/ntsim -lm -Wall -Wextra

assembler: src/ntasm.cpp
	g++ src/ntasm.cpp -o build/ntasm -lm -Wall -Wextra

terminal: src/terminal.cpp
	g++ src/terminal.cpp -o build/terminal -lm -Wall -Wextra

