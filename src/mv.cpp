#include "include/mv.h"
#include "include/label.h"
#include "include/result.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/types.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#include <ostream>
#include <vector>
#include <algorithm>

Mv::Mv() {
    program     = std::vector<Inst::BaseInst*>();
    label_table = std::map<std::string, Label::Label>();
    variables   = std::map<std::string, f32>();
    inst_ptr    = 0;
    halt        = false;
    debug       = false;

    heap = (u8*)calloc(10 * 1024 * 1024, sizeof(u8));
    srand(time(NULL));
}

Mv::~Mv() {
    for (usize i = 0; i < this->program.size(); ++i) {
        delete this->program[i];
    }
    free(heap);
}

Result<None> Mv::run() {
    if (debug) {
        for (const auto& [key, val] : label_table) {
            std::cout << "[ " << key << " ] = " 
                << "Label( " << val.m_name << " , " << val.m_jump_point << " )\n"; 
        }

        for (auto& inst : program) {
            inst->print();
        }
    }


    for (; inst_ptr < program.size() && !halt; ++inst_ptr) {
        Result r_inst = program[inst_ptr];

        if (r_inst.is_err()) {
          r_inst.get_err().fatal();
        }

        Inst::BaseInst* inst = r_inst.get_ok();

        if (debug) {
            std::cout << "=====================\n";
            inst->print();
            std::cout << "=====================\n";
        }

        Result r_exec = execute_inst(*inst);

        if (r_exec.is_err()) {
            return r_exec.get_err();
        }

    }

    return Void();
}

void Mv::add_inst(Inst::BaseInst* i) {
    program.push_back(i);
}

Result<None> Mv::execute_inst(const Inst::BaseInst& inst) {
    return inst.execute(*this);
}

Result<None> Mv::program_from_file(const char* filepath) {
    Lexer l(filepath); 

    std::vector<std::vector<Token>> tokens = l.tokenize_file();

    Parser p(tokens);
    std::vector<Inst::BaseInst*> program = p.parse_tokens(this);

    this->program = program;

    return Void();
}

Result<i32> Mv::include_program_from_file(std::string& filepath) {
    std::fstream f;
    std::string lib_path = std::string(getenv("HOME"))
                                        + "/.config/mvi/std/"
                                        + filepath;
    f.open(lib_path);
    bool use_lib = true;

    if (!f.is_open()) {
        use_lib = false;
        f.open(filepath);

        if (!f.is_open()) {
            f.close();
            return Err("Failed to open file");
        }
    }

    f.close();

    Lexer l((use_lib ? lib_path : filepath).c_str()); 

    std::vector<std::vector<Token>> tokens = l.tokenize_file();

    Parser p(tokens);
    std::vector<Inst::BaseInst*> program = p.parse_tokens(this);
    std::reverse(program.begin(), program.end());

    for (auto inst : program) {
        this->program.insert(this->program.begin(), inst);
    }

    return program.size();
}

i32 Mv::find_memory(usize len) {
    for (usize k = 0; k < 500; ++k) {
        for (size_t i = rand()%(4096-len); i < 4096 - len; i++) {
            size_t j;
            for (j = 0; j < len; j++) {
                if (heap[i + j] != 0) {
                    break; 
                }

                if (heap[i + j] == 0 && heap[i+j-1] != 0) {
                    break;
                }
            }

            if (j == len) {
                return i;
            }
        }
    }

    return -1;
    // -1 if no space was found
}
