#ifndef ASSEMBLY_H
#define ASSEMBLY_H 1

#include <string>
#include <ostream>
#include <vector>

struct ASM {
    std::string name;
    ASM(std::string name) : name(name) {}

    static const ASM GET, PUT, LOAD, STORE, LOADI, STOREI,
                    ADD, SUB, SHIFT, INC, DEC,  
                    JUMP, JPOS, JZERO, JNEG,
                    HALT;      
};

struct Instruction {
    private:
        Instruction(ASM command, int64_t label)
            : command(command), label(label) {}
        Instruction(ASM command, int64_t arg, int64_t label)
            : command(command), arg(arg), label(label) {}
    public:
        static const int64_t Undef = -1;

        ASM command;
        int64_t arg = Undef, label;


        // jumpy które potem będą miały dodane miejsca skoków

        static Instruction *JUMP(int64_t arg,int64_t *label) {
            return new Instruction(ASM::JUMP, (*label)++);
        }

        static Instruction *JPOS(int64_t arg,int64_t *label) {
            return new Instruction(ASM::JPOS, (*label)++);
        }

        static Instruction *JZERO(int64_t arg,int64_t *label) {
            return new Instruction(ASM::JZERO, (*label)++);
        }

        static Instruction *JNEG(int64_t arg,int64_t *label) {
            return new Instruction(ASM::JNEG, (*label)++);
        }


        // gotowe komendy

        static void GET(std::vector<Instruction*>& out, int64_t* label) {
                out.push_back(new Instruction(ASM::GET, (*label)++));
        }

        static void PUT(std::vector<Instruction*>& out, int64_t* label) {
                out.push_back(new Instruction(ASM::PUT, (*label)++));
        }

        static void LOAD(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::LOAD, arg, (*label)++));
        }

        static void STORE(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::STORE, arg, (*label)++));
        }

        static void LOADI(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::LOADI, arg, (*label)++));
        }

        static void STOREI(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::STOREI, arg, (*label)++));
        }

        static void ADD(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::ADD, arg, (*label)++));
        }

        static void SUB(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::SUB, arg, (*label)++));
        }

        static void SHIFT(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::SHIFT, arg, (*label)++));
        }

        static void INC(std::vector<Instruction*>& out, int64_t* label) {
                out.push_back(new Instruction(ASM::INC, (*label)++));
        }

        static void DEC(std::vector<Instruction*>& out, int64_t* label) {
                out.push_back(new Instruction(ASM::DEC, (*label)++));   
        }

        static void HALT(std::vector<Instruction*>& out, int64_t* label) {
                out.push_back(new Instruction(ASM::HALT, (*label)++));   
        }

        static void JUMP(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::JUMP, arg, (*label)++));  

        }
        static void JPOS(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::JPOS, arg, (*label)++));  
        }
        static void JZERO(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::JZERO, arg, (*label)++));  
        }
        static void JNEG(std::vector<Instruction*>& out, int64_t arg, int64_t* label) {
                out.push_back(new Instruction(ASM::JNEG, arg, (*label)++));  
        }


};

std::ostream & operator<<(std::ostream &stream, const Instruction &instruction);

#endif