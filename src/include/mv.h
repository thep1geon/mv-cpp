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
    Stack<i32, 1024> stack;
    Stack<i32, 1024> call_stack;
    std::vector<Inst::BaseInst*> program;
    std::map<std::string, Label::Label> label_table;
    std::map<std::string, i32> variables;
    i32 registers[10];
    i32 heap[sizeof(i32) * 1024];

    usize inst_ptr;

    bool halt;
    bool debug;

    Mv();
    ~Mv();

    void add_inst(Inst::BaseInst* i);
    Result<None> run();
    Result<None> execute_inst(const Inst::BaseInst& inst);

    Stack<i32, 1024>& get_stack();

    Result<None> program_from_file(const char* filepath);
    Result<i32> include_program_from_file(std::string& filepath);

    // Syscalls
    i32 find_memory(usize len);
};

#endif  //__MV_H
