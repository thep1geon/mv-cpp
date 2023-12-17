#ifndef __INST_H
#define __INST_H

#include "linkedlist.h"
#include "result.h"
#include "types.h"
#include "label.h"
#include "option.h"
#include "arg.h"
#include <map>
#include <string>

class Mv;

namespace Inst {

struct BaseInst {
    bool is_func = false;
    i32 m_line_num = 0;
    std::string m_file = "";

    LinkedList<Arg> args;

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

struct Func : public BaseInst {
public:
    Func();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Ret : public BaseInst {
public:
    Ret();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Call : public BaseInst {
public:
    Call();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Wait : public BaseInst {
public:
    Wait();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Size : public BaseInst {
public:
    Size();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

// Memory Stuff
struct Read : public BaseInst {
public:
    Read();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Write : public BaseInst {
public:
    Write();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Arr : public BaseInst {
public:
    Arr();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Str : public BaseInst {
public:
    Str();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

struct Include : public BaseInst {
public:
    Include();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

extern std::map<std::string, std::string> inst_map_str;
void init_inst_map(void);

struct Input : public BaseInst {
public:
    Input();
    void print() const override;
    Result<None> execute(Mv& mv) const override;
};

extern std::map<std::string, std::string> inst_map_str;
void init_inst_map(void);
}


#endif  //__INST_H
