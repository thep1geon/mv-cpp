#include "include/mv.h"
#include "include/label.h"
#include "include/result.h"
#include "include/lexer.h"
#include "include/stack.h"
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
    m_stack       = Stack<i32, 1024>();
    m_call_stack  = Stack<i32, 1024>();
    m_program     = std::vector<Inst::BaseInst*>();
    m_label_table = std::map<std::string, Label::Label>();
    m_inst_ptr    = 0;
    m_halt        = false;
    m_debug       = false;

    memset(heap, 0, 4096 * sizeof(i32));
}

Mv::~Mv() {
    for (usize i = 0; i < m_program.size(); ++i) {
        delete m_program[i];
    }

}

Result<None> Mv::run() {
    if (m_debug) {
        for (const auto& [key, val] : m_label_table) {
            std::cout << "[ " << key << " ] = " 
                << "Label( " << val.m_name << " , " << val.m_jump_point << " )\n"; 
        }

        for (auto& inst : m_program) {
            inst->print();
        }
    }

    for (; m_inst_ptr < m_program.size() && !m_halt; ++m_inst_ptr) {
        Result r_inst = m_program[m_inst_ptr];

        if (r_inst.is_err()) {
          r_inst.get_err().fatal();
        }

        Inst::BaseInst* inst = r_inst.get_ok();

        if (m_debug) {
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
    m_program.push_back(i);
}

Result<None> Mv::execute_inst(const Inst::BaseInst& inst) {
    return inst.execute(*this);
}

Stack<i32, 1024>& Mv::get_stack() {
    return m_stack;
}

Result<None> Mv::program_from_file(const char* filepath) {
    Lexer l(filepath); 

    std::vector<std::vector<Token>> tokens = l.tokenize_file();

    Parser p(tokens);
    std::vector<Inst::BaseInst*> program = p.parse_tokens(*this);

    m_program = program;

    return Void();
}

Result<i32> Mv::include_program_from_file(const char* filepath) {
    std::fstream f;
    f.open(filepath);

    if (!f.is_open()) {
        f.close();
        return Err("Failed to open file");
    }


    Lexer l(filepath); 

    std::vector<std::vector<Token>> tokens = l.tokenize_file();

    Parser p(tokens);
    std::vector<Inst::BaseInst*> program = p.parse_tokens(*this);
    std::reverse(program.begin(), program.end());

    for (auto inst : program) {
        m_program.insert(m_program.begin(), inst);
    }

    return program.size();
}

i32 Mv::find_memory(usize len) {
    srand(time(NULL));

    for (usize k = 0; k < 50; ++k) {
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
