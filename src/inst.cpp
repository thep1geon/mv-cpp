#include "include/arg.h"
#include "include/label.h"
#include "include/mv.h"
#include "include/inst.h"
#include "include/option.h"
#include "include/result.h"
#include "include/types.h"
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <vector>

#define ERR(msg) Err(msg, line_num, file)

Result<None> value_or_dot(Arg arg, i32* ptr, const Inst::BaseInst* i, const char* inst_type, Mv& mv) {
    if (arg.type == Arg::NUM) {
        *ptr = arg.get_num();
    } else if (arg.type == Arg::IDENT) {
        std::string ident = arg.get_str();

        if (ident == ".") {
            if (mv.stack.get_len() < 1) {
                return Err(std::string(inst_type)+": Stack Missing Elements. Cannot Perform Dot",
                           i->line_num, i->file);
            }
            *ptr = mv.stack.at(0).get_ok();
        } else if (ident == "..") {
            if (mv.stack.get_len() < 2) {
                return Err(std::string(inst_type)+": Stack Missing Elements. Cannot Perform Double-Dot",
                           i->line_num, i->file);
            }
            *ptr = mv.stack.at(1).get_ok();
        } else {
            return Err(std::string(inst_type)+": Invalid Ident", 
                       i->line_num, i->file);
        }
    } else {
        return Err(std::string(inst_type)+": Invalid Second Arguemnt Type. Expected NUM or IDENT, found STR", 
                   i->line_num, i->file);
    }

    return Void();
}

std::map<std::string, std::string> Inst::inst_map_str;

void Inst::init_inst_map(void) {
    Inst::inst_map_str["push"] = "push";
    Inst::inst_map_str["pop"] = "pop";
    Inst::inst_map_str["dupe"] = "dupe";
    Inst::inst_map_str["swap"] = "swap";

    Inst::inst_map_str["add"] = "add";
    Inst::inst_map_str["sub"] = "sub";
    Inst::inst_map_str["mult"] = "mult";
    Inst::inst_map_str["div"] = "div";
    Inst::inst_map_str["inc"] = "inc";
    Inst::inst_map_str["dec"] = "dec";

    Inst::inst_map_str["jmp"] = "jmp";
    Inst::inst_map_str["jmp_gt"] = "jmp_gt";
    Inst::inst_map_str["jmp_gteq"] = "jmp_gteq";
    Inst::inst_map_str["jmp_lt"] = "jmp_lt";
    Inst::inst_map_str["jmp_lteq"] = "jmp_lteq";
    Inst::inst_map_str["jmp_eq"] = "jmp_eq";
    Inst::inst_map_str["jmp_neq"] = "jmp_neq";

    Inst::inst_map_str["dump"] = "dump";
    Inst::inst_map_str["print"] = "print";
    Inst::inst_map_str["mov"] = "mov";
    Inst::inst_map_str["stop"] = "stop";
    Inst::inst_map_str["wait"] = "wait";
    Inst::inst_map_str["size"] = "size";

    Inst::inst_map_str["func"] = "func";
    Inst::inst_map_str["ret"] = "ret";
    Inst::inst_map_str["call"] = "call";

    Inst::inst_map_str["read"] = "read";
    Inst::inst_map_str["write"] = "write";
    Inst::inst_map_str["str"] = "str";
    Inst::inst_map_str["arr"] = "arr";

    Inst::inst_map_str["include"] = "include";

    Inst::inst_map_str["input"] = "input";
}

using namespace Inst;

// BaseInst
Result<None> BaseInst::execute(Mv& mv) const {
    mv.get_stack();
    return Void();
}
void BaseInst::print() const { 
    std::cout << "Base Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
BaseInst::~BaseInst() {}
// Inst::Add
Add::Add() {}
void Add::print() const {
    std::cout << "Add Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Add::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return ERR("Add: not enough elements on the stack");
    }

    return mv.get_stack().push(a.get_ok() + b.get_ok());
}

Sub::Sub() {}
void Sub::print() const {
    std::cout << "Sub Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Sub::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return ERR("Sub: not enough elements on the stack");
    }

    return mv.get_stack().push(a.get_ok() - b.get_ok());
}

// Inst::Multiply
Multiply::Multiply() {}
void Multiply::print() const {
    std::cout << "Multiply Inst\n"; 
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Multiply::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return ERR("Multiply: not enough elements on the stack");
    }

    return mv.get_stack().push(a.get_ok() * b.get_ok());
}

Divide::Divide() {}
void Divide::print() const {
    std::cout << "Divide Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Divide::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return ERR("Divide: not enough elements on the stack");
    }

    if (b.get_ok() == 0) {
        return ERR("Divide by zero error");
    }

    return mv.get_stack().push(a.get_ok() / b.get_ok());
}

Inc::Inc() {}
void Inc::print() const {
    std::cout << "Inc Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Inc::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return ERR("Inc: Empty Stack");
    }

    Result r_push = mv.get_stack().push(a.get_ok()+1);

    if (r_push.is_err()) {
        return ERR("Inc: Stack Overflow");
    }

    return Void();
}

Dec::Dec() {}
void Dec::print() const {
    std::cout << "Dec Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Dec::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return ERR("Dec: Empty Stack");
    }

    Result r_push = mv.get_stack().push(a.get_ok()-1);

    if (r_push.is_err()) {
        return ERR("Dec: Stack Overflow");
    }

    return Void();
}

// Jumps
Jump::Jump() {}
void Jump::print() const {
    std::cout << "Jump Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Jump::execute(Mv& mv) const {
    if (args.size() < 1) {
        return ERR("Jump: Missing Arguemnts");
    }

    if (args[0].type > Arg::NUM) {
        std::string literal = args[0].get_str();
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("Jump: Label/Func: "+ literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;

    } else {
        mv.inst_ptr = args[0].get_num();
    }

    return Void();
}

JumpGT::JumpGT() {}
void JumpGT::print() const {
    std::cout << "JumpGT Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpGT::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpGT: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpGT: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpGT: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpGT", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] > condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("JumpGT: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

JumpGTE::JumpGTE() {}
void JumpGTE::print() const {
    std::cout << "JumpGTE Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpGTE::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpGTE: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpGTE: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpGTE: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpGTE", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] >= condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("JumpGTE: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

JumpLT::JumpLT() {}
void JumpLT::print() const {
    std::cout << "JumpLT Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpLT::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpLT: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpLT: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpLT: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpLT", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] < condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("JumpLT: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

JumpLTE::JumpLTE() {}
void JumpLTE::print() const {
    std::cout << "JumpLTE Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpLTE::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpLTE: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpLTE: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpLTE: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpLTE", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] <= condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("JumpLTE: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

JumpEQ::JumpEQ() {}
void JumpEQ::print() const {
    std::cout << "JumpEQ Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpEQ::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpEQ: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpEQ: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpEQ: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpEQ", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] == condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name == "") {
            return ERR("JumpEQ: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

JumpNEQ::JumpNEQ() {}
void JumpNEQ::print() const {
    std::cout << "JumpNEQ Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> JumpNEQ::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("JumpNEQ: Missing Arguemnts");
    }

    if (mv.get_stack().peek().is_err()) {
        return ERR("JumpNEQ: Empty stack");
    }

    Arg arg_1 = args[0];
    Arg arg_2 = args[1];

    std::string literal;

    if (arg_1.type > Arg::NUM) {
        literal = arg_1.get_str(); 
    } else {
        return ERR("JumpNEQ: Invalid First Arguemnt");
    }

    i32 condition;

    Result r_cond = value_or_dot(arg_2, &condition, this, "JumpNEQ", mv);
    if (r_cond.is_err()) {return r_cond.get_err();}

    if (mv.stack[0] != condition) {
        Label::Label label = mv.label_table[literal];

        if (label.m_name != "") {
            return ERR("JumpNEQ: Label/Func: " + literal +" not found");
        }

        mv.inst_ptr = label.m_jump_point;
    }

    return Void();
}

// Inst::Push
Push::Push() {}
Push::Push(i32 operand) {
    args.push_back(Arg(operand));
}
void Push::print() const {
    std::cout << "Push Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Push::execute(Mv& mv) const {
    if (args.size() == 0) {
        return ERR("Push: Missing Argument");
    }

    for (usize i = 0; i < args.size(); ++i) {
        if (mv.stack.push(0).is_err()) {
            return ERR("Push: Stack Overflow");
        }

        mv.stack.pop();

        Arg a = args[i];

        if (a.type == Arg::NUM) {
            mv.stack.push(a.get_num());
        } else if (a.type == Arg::STR) {
            for (char c : a.get_str()) {
                mv.stack.push(c); 
            }
        }
    }

    return Void();
}

// Inst::Pop
Pop::Pop() {};
void Pop::print() const {
    std::cout << "Pop Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Pop::execute(Mv& mv) const {
    Result r = mv.get_stack().pop();

    if (r.is_err()) {
        return ERR("Pop : Stack Underflow");
    }

    if (args.size() == 1 && args[0].type == Arg::NUM) {
        mv.registers[args[0].get_num()] = r.get_ok(); 
    }

    return Void();
}

// Inst::Dupe
Dupe::Dupe() {}
void Dupe::print() const {
    std::cout << "Dupe Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Dupe::execute(Mv& mv) const {
    usize index = 0;
    if (args.size() == 1 && args[0].type == Arg::NUM) {
        index = args[0].get_num();
    }

    Result r_val = mv.get_stack().at(index);

    if (r_val.is_err()) {
        return ERR("Dupe: Empty Stack"); 
    }

    Result r_push = mv.get_stack().push(r_val.get_ok());

    if (r_push.is_err()) {
        return ERR("Dupe: Stack Overflow");
    }

    return Void();
}

// Inst::Swap
Swap::Swap() {}
void Swap::print() const {
    std::cout << "Swap Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Swap::execute(Mv& mv) const {
    Stack<i32, 1024>& s = mv.get_stack();
    Result a = s.pop();
    Result b = s.pop();

    if (a.is_err() || b.is_err()) {
        return ERR("Swap: Missing Elements From Stack");
    }

    Result a_push = s.push(a.get_ok());
    Result b_push = s.push(b.get_ok());

    return Void();
}

// Inst::Dump
Dump::Dump() {}
void Dump::print() const {
    std::cout << "Dump Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Dump::execute(Mv& mv) const {
    std::cout << "====Stack====\n";

    if (args.size() == 1 && args[0].type == Arg::NUM) {
        Result r = mv.stack.at(args[0].get_num()).get_ok();

        if (r.is_err()) {
            return ERR("Dump: index out of bounds");
        }

        std::cout << r.get_ok() << "\n";
    } else {
        mv.get_stack().print();
    }

    return Void();
}

Print::Print() {}
void Print::print() const {
    std::cout << "Print Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Print::execute(Mv& mv) const {
    if (args.size() == 1 && args[0].type == Arg::NUM) {
        Result r = mv.stack.at(args[0].get_num()).get_ok();

        if (r.is_err()) {
            return ERR("Print: index out of bounds");
        }

        std::cout << (char)r.get_ok();
    } else {

        Stack s = mv.get_stack();
        Stack<i32, 1024> ss;

        while (s.get_len() > 0) {
            ss.push(s.pop().get_ok());
        }

        while (ss.get_len() > 0) {
            std::cout << (char)ss.pop().get_ok();
        }
    }

    return Void();
}

Move::Move() {}
void Move::print() const {
    std::cout << "Move Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Move::execute(Mv& mv) const {
    // move dest src
    //      ni  ni
    i32 dst;
    i32 src_val;
    Option<i32> src;

    if (args.size() < 1) {
        return ERR("Move: Missing Argument(s)");
    }

    Result r_dst = value_or_dot(args[0], &dst, this, "Move", mv);
    if (r_dst.is_err()) {
        return r_dst.get_err();
    }


    if (args.size() > 1) {
        Result r_src_val = value_or_dot(args[1], &src_val, this, "Move", mv);
        if (r_src_val.is_err()) {
            return r_src_val.get_err();
        }

        src.set_value(src_val);
    }


    if (src.has_value()) {
        mv.registers[dst] = src_val;
    } else {
        return Push(mv.registers[dst]).execute(mv);
    }

    return Void();
}


Stop::Stop() {}
void Stop::print() const {
    std::cout << "Stop Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Stop::execute(Mv& mv) const {
    mv.halt = true;
    return Void();
}

LabelInst::LabelInst() {}
void LabelInst::print() const {
    std::cout << "Label Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> LabelInst::execute(Mv& mv) const {
    mv.inst_ptr += 0;
    return Void();
}

Func::Func() {}
void Func::print() const {
    std::cout << "Func Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Func::execute(Mv& mv) const {
    if (mv.call_stack.get_len() == 0) {
        Inst::Jump j = Inst::Jump();
        j.args.push_back(Arg(args[0].get_num()));
        j.file = file;
        j.line_num = line_num;
        return j.execute(mv);
    }

    return Void();
}

Ret::Ret() {}
void Ret::print() const {
    std::cout << "Ret Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Ret::execute(Mv& mv) const {
    if (mv.call_stack.get_len() != 0) {
        Inst::Jump j = Inst::Jump();

        j.args.push_back(Arg(mv.call_stack.pop().get_ok()));
        j.file = file;
        j.line_num = line_num;

        return j.execute(mv);
    }
    
    return Void();
}

Call::Call() {}
void Call::print() const {
    std::cout << "Call Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Call::execute(Mv& mv) const {
    if (args.size() < 1) {
        return ERR("Call: Not Enough Arguemnts");
    }

    if (args[0].type == Arg::NUM) {
        return ERR("Call: First Arguemnt: Invalid Type"); 
    }

    mv.call_stack.push(mv.inst_ptr);
    Inst::Jump j = Inst::Jump();

    j.args.push_back(Arg(args[0].get_str(), Arg::STR));
    j.file = file;
    j.line_num = line_num;

    return j.execute(mv);
}

Wait::Wait() {}
void Wait::print() const {
    std::cout << "Wait Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Wait::execute(Mv& mv) const {
    mv.get_stack();
    if (args.size() > 0 && args[0].type == Arg::NUM) {
        sleep(args[0].get_num()); 
    }

    return Void();
}

Size::Size() {}
void Size::print() const {
    std::cout << "Size Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Size::execute(Mv& mv) const {
    return Push(mv.get_stack().get_len()).execute(mv);
}

Read::Read() {}
void Read::print() const {
    std::cout << "Read Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Read::execute(Mv& mv) const {
    i32 address = 0;

    if (args.size() < 1) {
        return ERR("Read: Missing Argument"); 
    }

    if (mv.stack.get_len() + 1 >= 1024) {
        return ERR("Read: Stack Overflow");
    }

    Result r_adr = value_or_dot(args[0], &address, this, "Read", mv);
    if (r_adr.is_err()) {return r_adr.get_err();}

    return Push(mv.heap[address]).execute(mv);
}

Write::Write() {}
void Write::print() const {
    std::cout << "Write Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Write::execute(Mv& mv) const {
    if (args.size() < 2) {
        return ERR("Write: Missing Arguemnts");
    }
    
    i32 address = 0;
    i32 val     = 0;


    Result r_adr = value_or_dot(args[0], &address, this, "Write", mv);
    if (r_adr.is_err()) {return r_adr.get_err();}

    Result r_val = value_or_dot(args[1], &val, this, "Write", mv);
    if (r_val.is_err()) {return r_val.get_err();}

    mv.heap[address] = val;
    return Void();
}

Arr::Arr() {}
void Arr::print() const {
    std::cout << "Arr Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Arr::execute(Mv& mv) const {
    i32 len = 0;
    i32 def = -1;

    Result r_len = value_or_dot(args[0], &len, this, "Arr", mv);
    if (r_len.is_err()) {
        return r_len.get_err();
    }

    if (args.size() > 1) {
        Result r_def = value_or_dot(args[1], &def, this, "Arr", mv);
        if (r_def.is_err()) {
            return r_def.get_err();
        }
    }

    i32 start = mv.find_memory(len+1);

    if (start == -1) {
        return ERR("Arr: Memory Full: space for array not found");
    }

    for (i32 i = start; i < start + len; ++i) {
        mv.heap[i] = def;
    }

    return Inst::Push(start).execute(mv);
}

Str::Str() {}
void Str::print() const {
    std::cout << "Str Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Str::execute(Mv& mv) const {
    if (args.size() < 1) {
        return ERR("Str: Missing Argument");
    }
    std::string literal;

    if (args[0].type == Arg::STR) {
        literal = args[0].get_str();
    } else {
        return ERR("Str: Invalid Argument Type");
    }

    usize len = literal.length();
    i32 ptr = mv.find_memory(len+1);

    if (ptr == -1) {
        return ERR("Str: Memory Full: space for array not found");
    }

    usize i;
    usize s_ptr = 0;
    for (i = ptr; s_ptr < len && i < ptr + len; ++i) {
        mv.heap[i] = literal[s_ptr++];
    }

    mv.heap[++i] = '\0';

    Result r_len =  Inst::Push(len).execute(mv);
    Result r_ptr =  Inst::Push(ptr).execute(mv);

    if (r_len.is_err()) {
        return ERR("Str len: Stack Overflow");
    }

    if (r_ptr.is_err()) {
        return ERR("Str ptr: Stack Overflow");
    }

    return Void();
}

Include::Include() {}
void Include::print() const {
    std::cout << "Include Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Include::execute(Mv& mv) const {
    if (args.size() < 1) {
        return ERR("Include: Missing Argument");
    }

    if (args[0].type != Arg::STR) {
        return ERR("Include: Invalid Argument Type");
    }

    std::string literal = args[0].get_str();

    std::map<std::string, Label::Label> sec_map;

    sec_map = mv.label_table;

    Result r_include_file = mv.include_program_from_file(literal);

    if (r_include_file.is_err()) {
        return ERR("File: " + literal + " not found");
    }

    i32 offset = r_include_file.get_ok();
    mv.inst_ptr += offset;

    for (auto& [key, val] : sec_map) {
        val.m_jump_point += offset;
    }

    for (usize i = offset; i < mv.program.size(); ++i) {
        Inst::BaseInst*& inst = mv.program[i];
        if (inst->is_func) {
            Arg tmp = inst->args[0];
            inst->args[0] = inst->args[1];
            inst->args[1] = tmp;

            inst->args.pop_back();

            inst->args.insert(inst->args.begin(), Arg(tmp.get_num() + offset));
        } 
    }

    for (auto& [key, val] : mv.label_table) {
        if (sec_map.count(key) != 0) {
                mv.label_table[key] = sec_map[key];
        }

        if (mv.debug) {
            std::cout << "[ " << key << " ] = " 
                << "Label( " << val.m_name << " , " << val.m_jump_point << " )\n"; 
        }

    }

    return Void();
}

Input::Input() {}
void Input::print() const {
    std::cout << "Input Inst\n";
    for (Arg a : args) { std::cout << a << "\n";}
}
Result<None> Input::execute(Mv& mv) const {
    if (args.size() > 0 && args[0].type == Arg::STR) {
        std::cout << args[0].get_str();
    }

    i32 num;

    if (args.size() > 1 && args[1].type == Arg::NUM) {
        num = args[1].get_num();
    }

    scanf("%d", &num);

    Inst::Push push = Inst::Push(num);

    push.file = file;
    push.line_num = line_num;

    return push.execute(mv);
}
