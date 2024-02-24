#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cinttypes>
#include <ostream>


struct Instruction {
    typedef int64_t Immediate;
    enum class Opcode {
        add_ptr,
        add_val,
        input,
        output,
        branchz,
        branchnz,
    };
    Opcode opcode;
    Immediate imm;

    static Instruction add_value(Immediate imm) {
        return Instruction{Opcode::add_val, imm};
    }

    static Instruction add_pointer(Immediate imm) {
        return Instruction{Opcode::add_ptr, imm};
    }

    static Instruction input() {
        return Instruction{Opcode::input, 0};
    }

    static Instruction output() {
        return Instruction{Opcode::output, 0};
    }

    static Instruction branch_zero(Immediate jump_addr) {
        return Instruction{Opcode::branchz, jump_addr};
    }

    static Instruction branch_nonzero(Immediate jump_addr) {
        return Instruction{Opcode::branchnz, jump_addr};
    }
};


std::ostream &operator<<(std::ostream &os, const Instruction &ins);

#endif