#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <vector>
#include <stack>
#include "instruction.h"
#include "machine.h"

class Parser {
public:
    Parser() : instructions{}, open_bracket_indices{} {}

    bool parse(std::istream &is);

    auto get_instructions() const -> const std::vector<Instruction>& { return this->instructions; }

    void reset() {
        this->instructions.clear();
        while (!this->open_bracket_indices.empty()) { this->open_bracket_indices.pop(); }
    }

private:
    void parse_change_value(std::istream &is);

    void parse_change_pointer(std::istream &is);

    void parse_input(std::istream &is);

    void parse_output(std::istream &is);

    void parse_open_brace(std::istream &is);

    void parse_close_brace(std::istream &is);

    std::vector<Instruction> instructions;
    std::stack<std::vector<Instruction>::size_type> open_bracket_indices;

    bool unmatched_open_brace = false;
    bool unmatched_close_brace = false;
};

#endif