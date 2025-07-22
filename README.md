# Morris Mano's Basic Computer Emulator

A minimal emulator of Morris Mano’s Basic Computer architecture.
It uses a sequential counter to manage instruction flow and implements control logic for microinstruction execution.

## Project Structure

- src/ — source code files (C code in .cpp files)
- include/ — header files
- Makefile — build system

## About

- Core logic is written in C but placed in C++ files to facilitate future integration with Qt GUI.
- The emulator simulates the fetch-decode-execute cycle using a sequential counter for instruction sequencing.
- Control logic manages microinstructions to mimic the original Basic Computer behavior.
- Users can modify or load programs dynamically using the load_program function in main.cpp.

## Build

To build the project, run:
1. ```make```
2. `./build/program.out` or `.\build\program.exe`



## Future Work

- Implement Interrupts
- Integrate a Qt GUI for visualization and interaction.
- Expand the instruction set and add debugging features.
- Write an assembler for this Basic Computer emulator to simplify program creation.
