#include "include/label.h"
#include "include/mv.h"
#include "include/inst.h"
#include "include/option.h"
#include "include/result.h"
#include "include/types.h"
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

#define VAL_IF_SOME_NUM(opt) opt.has_value() ? opt.get_value().get_ok() : 0
#define VAL_IF_SOME_STR(opt) opt.has_value() ? opt.get_value().get_ok() : "NULL"


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
}

using namespace Inst;

// BaseInst
Result<None> BaseInst::execute(Mv& mv) const {
    mv.get_stack();
    return Void();
}
void BaseInst::print() const { 
    std::cout << "Base Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
// Inst::Add
Add::Add() {}
void Add::print() const {
    std::cout << "Add Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Add::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Add inst", m_line_num, m_file);
    }

    return mv.get_stack().push(a.get_ok() + b.get_ok());
}

Sub::Sub() {}
void Sub::print() const {
    std::cout << "Sub Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Sub::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Sub inst", m_line_num, m_file);
    }

    return mv.get_stack().push(a.get_ok() - b.get_ok());
}

// Inst::Multiply
Multiply::Multiply() {}
void Multiply::print() const {
    std::cout << "Multiply Inst\n"; 
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Multiply::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Multiply inst", m_line_num, m_file);
    }

    return mv.get_stack().push(a.get_ok() * b.get_ok());
}

Divide::Divide() {}
void Divide::print() const {
    std::cout << "Divide Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Divide::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Divide inst", m_line_num, m_file);
    }

    if (b.get_ok() == 0) {
        return Err("Divide by zero error", m_line_num, m_file);
    }

    return mv.get_stack().push(a.get_ok() / b.get_ok());
}

Inc::Inc() {}
void Inc::print() const {
    std::cout << "Inc Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Inc::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return Err("Inc Inst: Empty Stack", m_line_num, m_file);
    }

    Result r_push = mv.get_stack().push(a.get_ok()+1);

    if (r_push.is_err()) {
        return Err("Inc Inst: Stack Overflow", m_line_num, m_file);
    }

    return Void();
}

Dec::Dec() {}
void Dec::print() const {
    std::cout << "Dec Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Dec::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return Err("Inc Inst: Empty Stack", m_line_num, m_file);
    }

    Result r_push = mv.get_stack().push(a.get_ok()-1);

    if (r_push.is_err()) {
        return Err("Inc Inst: Stack Overflow", m_line_num, m_file);
    }

    return Void();
}

// Jumps
Jump::Jump() {}
void Jump::print() const {
    std::cout << "Jump Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Jump::execute(Mv& mv) const {
    usize jp;

    if (m_literal.has_value()) {
        Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

        if (label.m_name == "") {
            return Err("Jump: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
        }

        mv.m_inst_ptr = label.m_jump_point;

        return Void();
    }

    if (!m_operand_1.has_value()) {
        jp = mv.m_inst_ptr;
    } else {
        jp = m_operand_1.get_value().get_ok();
    }

    mv.m_inst_ptr = jp;

    return Void();
}

JumpGT::JumpGT() {}
void JumpGT::print() const {
    std::cout << "JumpGT Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpGT::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpGT Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpGT Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() > m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpGT: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

JumpGTE::JumpGTE() {}
void JumpGTE::print() const {
    std::cout << "JumpGTE Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpGTE::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpGTE Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpGTE Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() >= m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpGTE: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

JumpLT::JumpLT() {}
void JumpLT::print() const {
    std::cout << "JumpLT Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpLT::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpLT Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpLT Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() < m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpLT: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

JumpLTE::JumpLTE() {}
void JumpLTE::print() const {
    std::cout << "JumpLTE Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpLTE::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpLTE Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpLTE Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() <= m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpLTE: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

JumpEQ::JumpEQ() {}
void JumpEQ::print() const {
    std::cout << "JumpEQ Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpEQ::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpEQ Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpEQ Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() == m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpEQ: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

JumpNEQ::JumpNEQ() {}
void JumpNEQ::print() const {
    std::cout << "JumpNEQ Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> JumpNEQ::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("JumpNEQ Condition missing", m_line_num, m_file);
    }

    if (mv.get_stack().peek().is_err()) {
        return Err("JumpNEQ Empty stack", m_line_num, m_file);
    }

    if (mv.get_stack().peek().get_ok() != m_operand_1.get_value().get_ok()) {
        usize jp = mv.m_inst_ptr;

        if (m_literal.has_value()) {
            Label::Label label = mv.m_label_table[m_literal.get_value().get_ok()];

            if (label.m_name == "") {
                return Err("JumpNEQ: Label/Func: " + m_literal.get_value().get_ok() +" not found", m_line_num, m_file);
            }

            mv.m_inst_ptr = label.m_jump_point;

            return Void();
        }

        if (m_operand_1.has_value()) {
            jp = m_operand_1.get_value().get_ok();
        }

        mv.m_inst_ptr = jp;
    }

    return Void();
}

// Inst::Push
Push::Push() {}
Push::Push(i32 operand) {
    m_operand_1 = operand;
}
void Push::print() const {
    std::cout << "Push Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Push::execute(Mv& mv) const {
    if (m_literal.has_value()) {
        std::string lit = (VAL_IF_SOME_STR(m_literal));
        for (char c : lit) {
            mv.get_stack().push(c);
        }

        return Void();
    }

    else if (m_operand_1.has_value()) {
        Result r_push = mv.get_stack().push((VAL_IF_SOME_NUM(m_operand_1)));

        if (r_push.is_err()) {
            return Err("Push Inst: Stack Overflow", m_line_num, m_file);
        }

        return Void();
    } 

    return Err("Push Inst: Missing Operands", m_line_num, m_file);
}

// Inst::Pop
Pop::Pop() {};
void Pop::print() const {
    std::cout << "Pop Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Pop::execute(Mv& mv) const {
    Result r = mv.get_stack().pop();

    if (r.is_err()) {
        return Err("Pop Inst: Stack Underflow", m_line_num, m_file);
    }

    if (m_operand_1.has_value()) {
        mv.registers[(VAL_IF_SOME_NUM(m_operand_1))] = r.get_ok(); 
    }

    return Void();
}

// Inst::Dupe
Dupe::Dupe() {}
void Dupe::print() const {
    std::cout << "Dupe Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Dupe::execute(Mv& mv) const {
    usize index = 0;
    if (m_operand_1.has_value()) {
        index = m_operand_1.get_value().get_ok();
    }

    Result r_val = mv.get_stack().at(index);

    if (r_val.is_err()) {
        return Err("Dupe: Empty Stack", m_line_num, m_file); 
    }

    Result r_push = mv.get_stack().push(r_val.get_ok());

    if (r_push.is_err()) {
        return Err("Dupe: Stack Overflow", m_line_num, m_file);
    }

    return Void();
}

// Inst::Swap
Swap::Swap() {}
void Swap::print() const {
    std::cout << "Swap Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Swap::execute(Mv& mv) const {
    Stack<i32, 1024>& s = mv.get_stack();
    Result a = s.pop();
    Result b = s.pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Swap inst: inital pop", m_line_num, m_file);
    }

    Result a_push = s.push(a.get_ok());
    Result b_push = s.push(b.get_ok());

    if (a_push.is_err() || b_push.is_err()) {
        return Err("Failed to perform Swap inst: final pushes", m_line_num, m_file);
    }

    return Void();
}

// Inst::Dump
Dump::Dump() {}
void Dump::print() const {
    std::cout << "Dump Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Dump::execute(Mv& mv) const {
    std::cout << "====Stack====\n";

    if (m_operand_1.has_value()) {
        std::cout << mv.m_stack.at(m_operand_1.get_value().get_ok()).get_ok() << "\n";
    } else {
        mv.get_stack().print();
    }

    return Void();
}

Print::Print() {}
void Print::print() const {
    std::cout << "Print Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Print::execute(Mv& mv) const {
    if (m_operand_1.has_value()) {
        std::cout << (char)mv.m_stack.at(m_operand_1.get_value().get_ok()).get_ok();
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
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Move::execute(Mv& mv) const {
    if (m_operand_1.has_value() && !m_operand_2.has_value()) {
        return Push(mv.registers[(VAL_IF_SOME_NUM(m_operand_1))]).execute(mv);
    }

    if (!m_operand_1.has_value() || !m_operand_2.has_value()) {
        return Err("Failed to perform Move Inst\n    Either operand was missing", m_line_num, m_file);
    }

    if ((VAL_IF_SOME_NUM(m_operand_1)) > 10) {
        return Err("Failed to perform Move Inst\n    Reg index out of bounds", m_line_num, m_file);
    }

    mv.registers[(VAL_IF_SOME_NUM(m_operand_1))] = (VAL_IF_SOME_NUM(m_operand_2));
    return Void();
}


Stop::Stop() {}
void Stop::print() const {
    std::cout << "Stop Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Stop::execute(Mv& mv) const {
    mv.m_halt = true;
    return Void();
}

LabelInst::LabelInst() {}
void LabelInst::print() const {
    std::cout << "Label Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> LabelInst::execute(Mv& mv) const {
    mv.m_inst_ptr += 0;
    return Void();
}

Func::Func() {}
void Func::print() const {
    std::cout << "Func Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Func::execute(Mv& mv) const {
    if (mv.m_call_stack.get_len() == 0) {
        Inst::Jump j = Inst::Jump();
        j.m_operand_1 = m_operand_1;
        return j.execute(mv);
    }

    return Void();
}

Ret::Ret() {}
void Ret::print() const {
    std::cout << "Ret Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Ret::execute(Mv& mv) const {
    if (mv.m_call_stack.get_len() != 0) {
        Inst::Jump j = Inst::Jump();

        j.m_operand_1 = mv.m_call_stack.pop().get_ok();

        return j.execute(mv);
    }
    
    return Void();
}

Call::Call() {}
void Call::print() const {
    std::cout << "Call Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Call::execute(Mv& mv) const {
    mv.m_call_stack.push(mv.m_inst_ptr);
    Inst::Jump j = Inst::Jump();

    j.m_literal = m_literal;
    j.m_file = m_file;
    j.m_line_num = m_line_num;

    return j.execute(mv);
}

Wait::Wait() {}
void Wait::print() const {
    std::cout << "Wait Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Wait::execute(Mv& mv) const {
    mv.get_stack();
    if (m_operand_1.has_value()) {
        sleep((VAL_IF_SOME_NUM(m_operand_1))); 
    }

    return Void();
}

Size::Size() {}
void Size::print() const {
    std::cout << "Size Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Size::execute(Mv& mv) const {
    return Push(mv.get_stack().get_len()).execute(mv);
}

Read::Read() {}
void Read::print() const {
    std::cout << "Read Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Read::execute(Mv& mv) const {
    i32 address = 0;
    if (m_literal.has_value() && m_literal.get_value().get_ok() == ".") {
        Result r_address = mv.get_stack().peek();

        if (r_address.is_ok()) {
            address = r_address.get_ok();
        }

        return mv.get_stack().push(mv.heap[address]);
    }

    if (!m_operand_1.has_value()) {
        return Err("Read inst failed: missing address", m_line_num, m_file);
    }

    return mv.get_stack().push(mv.heap[m_operand_1.get_value().get_ok()]);
}

Write::Write() {}
void Write::print() const {
    std::cout << "Write Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Write::execute(Mv& mv) const {
    i32 address = 0;
    i32 val     = 0;

    if (m_literal.has_value() && m_literal.get_value().get_ok() == ".") {
        if (m_operand_1.has_value()) {
            Result r_val = mv.get_stack().peek();
            
            if (r_val.is_ok()) {
                val = r_val.get_ok();
            }
            
            address = m_operand_1.get_value().get_ok();

        } else if (m_operand_2.has_value()){
            Result r_add = mv.get_stack().peek();
            
            if (r_add.is_ok()) {
                address = r_add.get_ok();
            }
            
            val = m_operand_2.get_value().get_ok();
        } else {
            return Err("Write inst failed: Missing operand", m_line_num, m_file);
        }
    } else {
        if (!m_operand_1.has_value() || !m_operand_2.has_value()) {
            return Err("Write inst failed: Missing operand(s, m_line_num)", m_line_num, m_file);
        }
        
        address = m_operand_1.get_value().get_ok();
        val     = m_operand_2.get_value().get_ok();
    }

    mv.heap[address] = val;
    return Void();
}

Arr::Arr() {}
void Arr::print() const {
    std::cout << "Arr Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Arr::execute(Mv& mv) const {
    usize len = 0;
    i32 def = -1;

    if (m_operand_1.has_value()) {
        len = m_operand_1.get_value().get_ok();
    }

    if (m_operand_2.has_value()) {
        def = m_operand_2.get_value().get_ok();
    }

    i32 start = mv.find_memory(len+1);

    if (start == -1) {
        return Err("Arr: Memory Full: space for array not found", m_line_num, m_file);
    }

    for (usize i = start; i < start + len; ++i) {
        mv.heap[i] = def;
    }

    return Inst::Push(start).execute(mv);
}

Str::Str() {}
void Str::print() const {
    std::cout << "Str Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Str::execute(Mv& mv) const {
    if (!m_literal.has_value()) {
        return Err("Str: missing string", m_line_num, m_file);
    }

    usize len = m_literal.get_value().get_ok().length();
    i32 ptr = mv.find_memory(len+1);

    if (ptr == -1) {
        return Err("Str: Memory Full: space for array not found", m_line_num, m_file);
    }

    std::string s = m_literal.get_value().get_ok();

    usize i;
    usize s_ptr = 0;
    for (i = ptr; s_ptr < len && i < ptr + len; ++i) {
        mv.heap[i] = s[s_ptr++];
    }

    mv.heap[++i] = '\0';

    Result r_len =  Inst::Push(len).execute(mv);
    Result r_ptr =  Inst::Push(ptr).execute(mv);

    if (r_len.is_err()) {
        return Err("Str len: Stack Overflow", m_line_num, m_file);
    }

    if (r_ptr.is_err()) {
        return Err("Str ptr: Stack Overflow", m_line_num, m_file);
    }

    return Void();
}

Include::Include() {}
void Include::print() const {
    std::cout << "Include Inst\n";
    std::cout << "    operand 1: " << (VAL_IF_SOME_NUM(m_operand_1)) << "\n";
    std::cout << "    operand 2: " << (VAL_IF_SOME_NUM(m_operand_2)) << "\n";
    std::cout << "    literal:   " << (VAL_IF_SOME_STR(m_literal)) << "\n";
}
Result<None> Include::execute(Mv& mv) const {
    if (!m_literal.has_value()) {
        return Err("Include Inst missing file", m_line_num, m_file);
    }

    std::map<std::string, Label::Label> sec_map;

    sec_map = mv.m_label_table;

    Result r_include_file = mv.include_program_from_file(m_literal.get_value().get_ok().c_str());

    i32 offset = r_include_file.get_ok();
    mv.m_inst_ptr += offset;

    for (auto& [key, val] : sec_map) {
        val.m_jump_point += offset;
    }

    for (auto& [key, val] : mv.m_label_table) {
        if (sec_map.count(key) != 0) {
                mv.m_label_table[key] = sec_map[key];
        }

        if (mv.m_debug) {
            std::cout << "[ " << key << " ] = " 
                << "Label( " << val.m_name << " , " << val.m_jump_point << " )\n"; 
        }

    }

    if (mv.m_debug) {
        for (auto inst : mv.m_program) {
            inst->print();
        }
    }

    return Void();
}
