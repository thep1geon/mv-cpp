#ifndef __MV_H
#define __MV_H

#include "inst.h"
#include "label.h"
#include "result.h"
#include "stack.h"
#include "types.h"
#include <map>
#include <vector>

struct Mv {
    Stack<i32, 1024> m_stack;
    Stack<i32, 1024> m_call_stack;
    std::vector<Inst::BaseInst*> m_program;
    std::map<std::string, Label::Label> m_label_table;
    i32 registers[10];
    i32 heap[sizeof(i32) * 1024];

    usize m_inst_ptr;

    bool m_halt;
    bool m_debug;

    Mv();
    ~Mv();

    void add_inst(Inst::BaseInst* i);
    Result<None> run();
    Result<None> execute_inst(const Inst::BaseInst& inst);

    Stack<i32, 1024>& get_stack();

    Result<None> program_from_file(const char* filepath);
    Result<i32> include_program_from_file(const char* filepath);

    i32 find_memory(usize len);
};

#endif  //__MV_H
