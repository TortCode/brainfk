#include <cstdio>
#include "parser.h"

bool Parser::parse(std::istream &is) {
    char c;
    while ((c = is.peek()) != EOF) {
        switch (c) {
            case '+': case '-':
                this->parse_change_value(is);
                break;
            case '<': case '>':
                this->parse_change_pointer(is);
                break;
            case '.':
                this->parse_output(is);
                break;
            case ',':
                this->parse_input(is);
                break;
            case '[':
                this->parse_open_brace(is);
                break;
            case ']':
                this->parse_close_brace(is);
                break;
            default:
                is.ignore();
        }

        if (this->unmatched_close_brace) {
            return false;
        }
    }

    if (!this->open_bracket_indices.empty()) {
        this->unmatched_open_brace = true;
        return false;
    }

    return true;
}

void Parser::parse_change_value(std::istream &is)
{
    char c;
    Machine::value_type accumulator = 0;
    while ((c = is.peek()) != EOF) {
        if (c == '+') {
            accumulator++;
        } else if (c == '-') {
            accumulator--;
        } else {
            break;
        }
        is.ignore();
    }

    this->instructions.push_back(Instruction::add_value(accumulator));
}

void Parser::parse_change_pointer(std::istream &is)
{
    char c;
    Machine::offset_type accumulator = 0;
    while ((c = is.peek()) != EOF) {
        if (c == '>') {
            accumulator++;
        } else if (c == '<') {
            accumulator--;
        } else {
            break;
        }
        is.ignore();
    }

    this->instructions.push_back(Instruction::add_pointer(accumulator));
}

void Parser::parse_input(std::istream& is)
{
    this->instructions.push_back(Instruction::input());
    is.ignore();
}

void Parser::parse_output(std::istream& is)
{
    this->instructions.push_back(Instruction::output());
    is.ignore();
}

void Parser::parse_open_brace(std::istream& is)
{
    this->open_bracket_indices.push(this->instructions.size());
    this->instructions.push_back(Instruction::branch_zero(0));
    is.ignore();
}

void Parser::parse_close_brace(std::istream& is)
{
    if (this->open_bracket_indices.empty()) {
        this->unmatched_close_brace = true;
        return;
    }
    auto open_bracket_index = this->open_bracket_indices.top();
    this->open_bracket_indices.pop();

    this->instructions[open_bracket_index].imm = this->instructions.size();
    this->instructions.push_back(Instruction::branch_nonzero(open_bracket_index));
    is.ignore();
}
