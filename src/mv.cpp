#include "include/mv.h"
#include "include/result.h"
#include "include/lexer.h"
#include "include/stack.h"
#include "include/parser.h"
#include <vector>

Mv::Mv() {
    m_stack = Stack<i32, 1024>();
    m_program = std::vector<Inst::BaseInst*>();
    m_inst_ptr = 0;
    m_halt = false;
}

Mv::~Mv() {
    for (usize i = 0; i < m_program.size(); ++i) {
        delete m_program[i];
    }
}

Result<None> Mv::run() {
    for (; m_inst_ptr < m_program.size() && !m_halt; ++m_inst_ptr) {
        Result r_inst = m_program[m_inst_ptr];

        if (r_inst.is_err()) {
          r_inst.get_err().fatal();
        }

        Inst::BaseInst* inst = r_inst.get_ok();

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
