#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include "engine.h"
#include "parser.h"

// #define DEBUG

void usage() {
    puts("Usage: bf [-c cmd | -f file | - ]");
    printf("%5s     %-s\n", "-h", "help");
}

void run_round(Engine &engine, std::istream &is) {
    Parser p{};
    p.parse(is);

    const auto &instructions = p.get_instructions();
#ifdef DEBUG
    for (uint i = 0; i < instructions.size(); i++) {
        std::cout << i << ": " << instructions[i] << std::endl;
    }
#endif

    engine.load_instructions(instructions);

    while (!engine.is_done()) { engine.step(); }
}

void run_bf(std::istream &is) {
    Engine engine{};
    run_round(engine, is);
}

void file_bf(char *filename) {
    if (strcmp(filename, "-") == 0) {
        run_bf(std::cin);
    } else {
        std::ifstream input_file{filename};
        run_bf(input_file);
    }

}

void cmd_bf(const char *cmd) {
    std::istringstream ss{cmd};
    run_bf(ss);
}

void repl_bf() {
    Engine engine{};
    for (std::string line; std::cout << "> ", std::getline(std::cin, line);) {
        std::istringstream ss{line};
        run_round(engine, ss);
        std::cin.ignore(1, '\n');
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        repl_bf();
        return EXIT_SUCCESS;
    }

    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            usage();
            return EXIT_SUCCESS;
        }
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 >= argc) {
                std::cerr << "Must supply command to option -c." << std::endl;
                return EXIT_FAILURE;
            }

            cmd_bf(argv[i+1]);
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) {
                std::cerr << "Must supply filename to option -f." << std::endl;
                return EXIT_FAILURE;
            }

            file_bf(argv[i+1]);
            return EXIT_SUCCESS;
        }
    }

    file_bf(argv[1]);

    return EXIT_SUCCESS;
}
