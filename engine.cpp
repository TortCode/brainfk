#include <cstdio>
#include <iostream>
#include "engine.h"

void Engine::step()
{
    if (this->iptr>=this->instructions.size()) {
        this->done = true;
        return;
    }

    Machine::Status status = Machine::Status::ok;
    Instruction instruction = this->instructions[this->iptr];
    switch (instruction.opcode) {
    case Instruction::Opcode::add_ptr:
#ifdef DEBUG
        printf("Moving %ld\n", instruction.imm);
#endif
        status = this->machine.add_pointer(instruction.imm);
        if (status==Machine::Status::negative_address) {
            printf("Negative address at instruction %ld\n", this->iptr);
            this->done = true;
            return;
        }
        if (status==Machine::Status::out_of_memory) {
            printf("Out of memory at instruction %ld\n", this->iptr);
            this->done = true;
            return;
        }
        break;
    case Instruction::Opcode::add_val:
#ifdef DEBUG
        printf("Adding %ld\n", instruction.imm);
#endif
        status = this->machine.add_value(instruction.imm);
        if (status==Machine::Status::integer_overflow) {
            printf("Overflow at instruction %ld\n", this->iptr);
            this->done = true;
            return;
        }
        break;
    case Instruction::Opcode::input: {
#ifdef DEBUG
        puts("Getting");
#endif
        char c;
        std::cin >> c;
        this->machine.set_value(c);
        break;
    }
    case Instruction::Opcode::output: {
#ifdef DEBUG
        puts("Putting");
#endif
        char c = this->machine.get_value();
        putchar(c);
        putchar('\n');
        break;
    }
    case Instruction::Opcode::branchz: {
        Machine::value_type val = this->machine.get_value();
        if (val==0) {
#ifdef DEBUG
            puts("Forward loop pass");
#endif
            this->iptr = instruction.imm;
        }
        break;
    }
    case Instruction::Opcode::branchnz: {
        Machine::value_type val = this->machine.get_value();
        if (val!=0) {
#ifdef DEBUG
            puts("Backward loop pass");
#endif
            this->iptr = instruction.imm;
        }
        break;
    }
    default:
#ifdef DEBUG
        printf("Unknown instruction %lx\n", static_cast<uint64_t>(instruction.opcode));
#endif
        break;
    }

    this->iptr++;
}