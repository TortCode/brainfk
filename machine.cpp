#include "machine.h"

auto Machine::add_pointer(offset_type offset) -> Status
{
    if (offset<0) {
        if (this->addr<-offset) {
            return Status::negative_address;
        }
    }
    else if (this->addr+offset>=this->mem.size()) {
        try {
            this->mem.resize(this->addr+offset+1);
        }
        catch (std::bad_alloc& err) {
            return Status::out_of_memory;
        }
    }

    this->addr += offset;
    return Status::ok;
}

static auto check_overflow(Machine::value_type x, Machine::value_type y, Machine::value_type s) -> bool
{
    if (x>0 && y>0 && s<0)
        return true;
    if (x<0 && y<0 && s>0)
        return true;
    return false;
}

auto Machine::add_value(value_type val) -> Status
{
    value_type old_val = this->mem[this->addr];
    value_type new_val = old_val+val;
    if (check_overflow(old_val, val, new_val)) {
        return Status::integer_overflow;
    }

    this->mem[this->addr] = new_val;
    return Status::ok;
}

void Machine::set_value(value_type val)
{
    this->mem[this->addr] = val;
}

auto Machine::get_value() const -> value_type
{
    return this->mem[this->addr];
}