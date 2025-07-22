# Morris Mano's Basic Computer Emulator

A minimal emulator of Morris Mano’s Basic Computer architecture with Qt GUI integration.

It uses a sequential counter to manage instruction flow and control logic for microinstruction execution.  
The GUI emulates a 512×256 memory-mapped pixel screen, showing real output based on executed instructions.

---

## Project Structure

- `src/` — Source files (`.cpp`)
- `include/` — Header files
- `Makefile` — Build system
- `build/ManoMachineEmulator.exe` — Output binary

---

## About

- Core logic written in C, wrapped in C++ for Qt integration.
- Simulates fetch-decode-execute cycle with sequential instruction counter.
- Microinstruction control logic mimics original Basic Computer.
- GUI reads memory to emulate real screen output.
- Programs can be loaded/modified dynamically via `load_program()` in `computer.cpp`.

---

## Example Program

```assembly
ORG 050
SCREEN,   HEX C80F
PIXELS,   HEX FFFF

ORG 100
START,    LDA PIXELS
          STA I SCREEN
          HLT
END
```

```c
void load_program(Computer* comp) {
    memset(comp->mem->data, 0, 65536 * sizeof(uint16_t));
    comp->PC->value = 0x100;

    comp->mem->data[0x100] = 0x2051; // LDA PIXELS
    comp->mem->data[0x101] = 0xB050; // STA I SCREEN
    comp->mem->data[0x102] = 0x7001; // HLT

    comp->mem->data[0x050] = 0xC80F; // SCREEN base address
    comp->mem->data[0x051] = 0xFFFF; // PIXELS pattern
}
```

## Run
```bash
make
.\build\ManoMachineEmulator.exe or ./build/ManoMachineEmulator.out
```
