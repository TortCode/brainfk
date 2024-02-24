#include "instruction.h"

std::ostream &operator<<(std::ostream &os, const Instruction &ins) {
    static const char *const opcode_to_string[] = {
        "add_ptr",
        "add_val",
        "input",
        "output",
        "branchz",
        "branchnz",
    };
    std::string opcode_str = opcode_to_string[static_cast<int>(ins.opcode)];
    os << opcode_str << "    " << ins.imm;
    return os;
}