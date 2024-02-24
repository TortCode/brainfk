#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <cinttypes>
#include "machine.h"
#include "instruction.h"

// #define DEBUG

class Engine {
public:
    typedef uint64_t size_type;

    Engine() = default;

    /**
     * Load instructions into engine
     */
    void load_instructions(const std::vector<Instruction> &ins) {
        this->instructions = ins;
        this->iptr = 0;
        this->done = false;
    }

    /**
     * Run one step of engine
     * @return Whether the engine is still in a valid state and not finished
     */
    void step();

    bool is_done() { return this->done; }

private:
    Machine machine{};
    std::vector<Instruction> instructions{};
    size_type iptr{0};

    bool done{false};
};

#endif