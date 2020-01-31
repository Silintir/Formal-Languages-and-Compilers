#include "asm.hpp"

const ASM ASM::GET    = {"GET"};
const ASM ASM::PUT    = {"PUT"};

const ASM ASM::LOAD   = {"LOAD"};
const ASM ASM::STORE  = {"STORE"};
const ASM ASM::LOADI  = {"LOADI"};
const ASM ASM::STOREI = {"STOREI"};

const ASM ASM::ADD    = {"ADD"};
const ASM ASM::SUB    = {"SUB"};
const ASM ASM::SHIFT  = {"SHIFT"};
const ASM ASM::INC    = {"INC"};
const ASM ASM::DEC    = {"DEC"};

const ASM ASM::JUMP   = {"JUMP"};
const ASM ASM::JPOS   = {"JPOS"};
const ASM ASM::JZERO  = {"JZERO"};
const ASM ASM::JNEG   = {"JNEG"};
const ASM ASM::HALT   = {"HALT"};

std::ostream & operator<<(std::ostream &stream, const Instruction &instruction) {
    stream << instruction.command.name;
    if(instruction.arg != Instruction::Undef) {
        stream << " " << instruction.arg;
    }
    return stream << "\n";
}