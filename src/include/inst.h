#ifndef __INST_H
#define __INST_H

#include "result.h"
#include "types.h"
#include "label.h"
#include "option.h"
#include <map>
#include <string>

class Mv;

namespace Inst {
struct BaseInst {
    Option<i32> m_operand_1 = Option<i32>();
    Option<i32> m_operand_2 = Option<i32>();
    Option<std::string> m_literal = Option<std::string>();
    virtual ~BaseInst() = default;
    virtual void print() const;
    virtual Result<None> execute(Mv& mv) const;
};

// Math related Insts
struct Add : public BaseInst {
    Add();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Sub : public BaseInst {
    Sub();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Multiply : public BaseInst {
    Multiply();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Divide : public BaseInst {
    Divide();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Inc : public BaseInst {
    Inc();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Dec : public BaseInst {
    Dec();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

// Insts related to jumping around the program
struct Jump : public BaseInst {
    Jump();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpGT : public BaseInst {
    JumpGT();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpGTE : public BaseInst {
    JumpGTE();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpLT : public BaseInst {
    JumpLT();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpLTE : public BaseInst {
    JumpLTE();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpEQ : public BaseInst {
    JumpEQ();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

struct JumpNEQ : public BaseInst {
    JumpNEQ();
    void print() const override;
    Result<None> execute(Mv& mv) const override; 
};

// Stack related Insts
struct Push : public BaseInst {
    Push();
    Push(i32 operand);
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Pop : public BaseInst {
    Pop();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Dupe: public BaseInst {
    Dupe();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Swap : public BaseInst {
    Swap();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

// Misc Insts
struct Dump : public BaseInst {
public:
    Dump();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Print : public BaseInst {
public:
    Print();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Move : public BaseInst {
public:
    Move();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Stop : public BaseInst {
public:
    Stop();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct LabelInst : public BaseInst {
public:
    LabelInst();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

// struct INST : public BaseInst {
// public:
//     INST();
//     void print() const override;
//     Result<None> execute(Mv& mv) const override;
// };

extern std::map<std::string, std::string> inst_map_str;
void init_inst_map(void);

}


#endif  //__INST_H
