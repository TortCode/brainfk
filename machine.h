#ifndef MACHINE_H
#define MACHINE_H

#include <cinttypes>
#include <vector>

class Machine {
public:
    enum class Status {
        ok,
        negative_address,
        out_of_memory,
        integer_overflow,
    };

    typedef int64_t value_type;
    typedef uint64_t size_type;
    typedef int64_t offset_type;

    Machine()
            :mem(64), addr(0) { }

    /**
     * Move the pointer of an machine
     * @param offset - the offset to add_pointer the pointer by
     * @return status of machine after moving
     */
    auto add_pointer(offset_type offset) -> Status;

    /**
     * Add a value to the current cell of an machine
     * @param val - the value to add
     * @return status of machine after adding
     */
    auto add_value(value_type val) -> Status;

    /**
     * Sets the value of the current cell of the machine
     * @param val - value to set cell pointed to by pointer to
     */
    void set_value(value_type val);

    /**
     * Gets the value of the current cell of the machine
     * @return value contained within cell pointed to by pointer
     */
    auto get_value() const -> value_type;

private:
    std::vector<value_type> mem;
    size_type addr;
};

#endif