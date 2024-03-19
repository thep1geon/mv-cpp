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
    Stack<f32> stack = Stack<f32>();
    Stack<i32> call_stack = Stack<i32>();
    std::vector<Inst::BaseInst*> program;
    std::map<std::string, Label::Label> label_table;
    std::map<std::string, f32> variables;
    i32 registers[10];
    u8* heap;

    usize inst_ptr;

    bool halt;
    bool debug;

    Mv();
    ~Mv();

    void add_inst(Inst::BaseInst* i);
    Result<None> run();
    Result<None> execute_inst(const Inst::BaseInst& inst);

    Result<None> program_from_file(const char* filepath);
    Result<i32> include_program_from_file(std::string& filepath);

    // Syscalls
    i32 find_memory(usize len);
};

#endif  //__MV_H
