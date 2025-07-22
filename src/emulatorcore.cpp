#include "emulatorcore.h"
#include "config.h"


// constructor for bridge class EmulatorCore
// init computer and load program
EmulatorCore::EmulatorCore(QObject* parent): QObject(parent){
    init_computer(&m_computer);
    load_program(&m_computer);
}


EmulatorCore::~EmulatorCore(){
    free_computer(&m_computer);
}

const uint16_t* EmulatorCore::  getVideoBuffer() const {
    return m_computer.mem->data + VRAM_START_ADDR;
}


void EmulatorCore:: tick(){
    if (check_flag(m_computer.flags, R) == 1) {
        interrupt_service(&m_computer); 
        
    }
    else if(check_flag(m_computer.flags, S) == 1){
        std::printf("Noldu Moruk:\n");
        fetch(&m_computer);
        decode(&m_computer);
        //if needed
        

        if (m_computer.i->opcode != 7 && check_flag(m_computer.flags, I) == 1) {
            indirect(&m_computer);
        }
        else increment_register(m_computer.SC);

        while(read_register(m_computer.SC) != 0) execute(&m_computer);
    }
    else{
        emit computerHalted();
        return;
    } 

    if (check_flag(m_computer.flags, IEN) == 1 &&
       (check_flag(m_computer.flags, FGI) == 1 || check_flag(m_computer.flags, FGO) == 1))
    {
        set_flag(m_computer.flags, R);
    }
    emit screenUpdated();
}

void EmulatorCore:: handleKeyPress(char code){
    write_register(m_computer.INPR, code);
    set_flag(m_computer.flags, FGI);
}