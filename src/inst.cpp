#include "include/mv.h"
#include "include/inst.h"
#include "include/option.h"
#include "include/result.h"
#include <iostream>
#include <string>


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

    Inst::inst_map_str["dump"] = "dump";
    Inst::inst_map_str["mov"] = "mov";
    Inst::inst_map_str["stop"] = "stop";
}

using namespace Inst;

// BaseInst
Result<None> BaseInst::execute(Mv& mv) const {
    mv.get_stack();
    return None();
}
void BaseInst::print() const { std::cout << "Base Inst\n"; }

// Inst::Add
Add::Add() {}
void Add::print() const {std::cout << "Add Inst\n";}
Result<None> Add::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Add inst");
    }

    return mv.get_stack().push(a.get_ok() + b.get_ok());
}

Sub::Sub() {}
void Sub::print() const {std::cout << "Sub Inst\n";}
Result<None> Sub::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Sub inst");
    }

    return mv.get_stack().push(a.get_ok() - b.get_ok());
}

// Inst::Multiply
Multiply::Multiply() {}
void Multiply::print() const {std::cout << "Multiply Inst\n"; }
Result<None> Multiply::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Multiply inst");
    }

    return mv.get_stack().push(a.get_ok() * b.get_ok());
}

Divide::Divide() {}
void Divide::print() const {std::cout << "Divide Inst\n";}
Result<None> Divide::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();
    Result b = mv.get_stack().pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Divide inst");
    }

    if (b.get_ok() == 0) {
        return Err("Divide by zero error");
    }

    return mv.get_stack().push(a.get_ok() / b.get_ok());
}

Inc::Inc() {}
void Inc::print() const {std::cout << "Inc Inst\n";}
Result<None> Inc::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return Err("Failed to perform Inc inst");
    }

    return mv.get_stack().push(a.get_ok()+1);
}

Dec::Dec() {}
void Dec::print() const {std::cout << "Dec Inst\n";}
Result<None> Dec::execute(Mv& mv) const {
    Result a = mv.get_stack().pop();

    if (a.is_err()) {
        return Err("Failed to perform Dec inst");
    }

    return mv.get_stack().push(a.get_ok()-1);
}

// Jumps
Jump::Jump() {}
void Jump::print() const {
    std::cout << "Jump Inst\n";
    std::cout << "    Jump Point: " << m_operand_1.get_value().get_ok() << "\n";
}
Result<None> Jump::execute(Mv& mv) const {
    usize jp;

    if (m_literal.has_value()) {
        mv.m_inst_ptr = mv.m_label_table[m_literal.get_value().get_ok()].m_jump_point;
        return None();
    }

    if (!m_operand_1.has_value()) {
        jp = mv.m_inst_ptr;
    } else {
        jp = m_operand_1.get_value().get_ok();
    }

    mv.m_inst_ptr = jp;

    return None();
}

// Inst::Push
Push::Push() {}
Push::Push(i32 operand) {
    m_operand_1 = operand;
}
void Push::print() const {
    std::cout << "Push Inst\n";
    std::cout << "    Push Value: " << m_operand_1.get_value().get_ok() << "\n";
}
Result<None> Push::execute(Mv& mv) const {
    if (!m_operand_1.has_value()) {
        return Err("Failed to perform Push inst");
    }

    return mv.get_stack().push(m_operand_1.get_value().get_ok());
}

// Inst::Pop
Pop::Pop() {};
void Pop::print() const {std::cout << "Pop Inst\n";}
Result<None> Pop::execute(Mv& mv) const {
    Result r = mv.get_stack().pop();

    if (r.is_err()) {
        return r.get_err();
    }

    if (m_operand_1.has_value()) {
        mv.registers[m_operand_1.get_value().get_ok()] = r.get_ok(); 
    }

    return None();
}

// Inst::Dupe
Dupe::Dupe() {}
void Dupe::print() const {std::cout << "Dupe Inst\n";}
Result<None> Dupe::execute(Mv& mv) const {
    Result top = mv.get_stack().peek();

    if (top.is_err()) {
        return top.get_err(); 
    }

    return mv.get_stack().push(top.get_ok());
}

// Inst::Swap
Swap::Swap() {}
void Swap::print() const {std::cout << "Swap Inst\n";}
Result<None> Swap::execute(Mv& mv) const {
    Stack<i32, 1024>& s = mv.get_stack();
    Result a = s.pop();
    Result b = s.pop();

    if (a.is_err() || b.is_err()) {
        return Err("Failed to perform Swap inst: inital pop");
    }

    Result a_push = s.push(a.get_ok());
    Result b_push = s.push(b.get_ok());

    if (a_push.is_err() || b_push.is_err()) {
        return Err("Failed to perform Swap inst: final pushes");
    }

    return None();
}

// Inst::Dump
Dump::Dump() {}
void Dump::print() const {std::cout << "Dump Inst\n";}
Result<None> Dump::execute(Mv& mv) const {
    mv.get_stack().print();
    return None();
}

Move::Move() {}
void Move::print() const {std::cout << "Move Inst\n";}
Result<None> Move::execute(Mv& mv) const {
    if (m_operand_1.has_value() && !m_operand_2.has_value()) {
        return Push(mv.registers[m_operand_1.get_value().get_ok()]).execute(mv);
    }

    if (!m_operand_1.has_value() || !m_operand_2.has_value()) {
        return Err("Failed to perform Move Inst\n\rEither operand was missing");
    }

    if (m_operand_1.get_value().get_ok() > 10) {
        return Err("Failed to perform Move Inst\n\rReg index out of bounds");
    }

    mv.registers[m_operand_1.get_value().get_ok()] = m_operand_2.get_value().get_ok();
    return None();
}


Stop::Stop() {}
void Stop::print() const {std::cout << "Stop Inst\n";}
Result<None> Stop::execute(Mv& mv) const {
    mv.m_halt = true;
    return None();
}

LabelInst::LabelInst() {}
void LabelInst::print() const {std::cout << "Label Inst\n";}
Result<None> LabelInst::execute(Mv& mv) const {
    mv.m_inst_ptr += 0;
    return None();
}
