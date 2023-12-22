#ifndef __PARSER_H
#define __PARSER_H

#include <vector>
#include "lexer.h"
#include "linkedlist.h"
#include "inst.h"

class Mv;

class Parser {
    std::vector<std::vector<Token>> m_tokens;
    std::vector<Inst::BaseInst*> m_program;
public:
    Parser(std::vector<std::vector<Token>> tokens);
    ~Parser() = default;

    const std::vector<Inst::BaseInst*> parse_tokens(Mv* mv);
};

#endif  //__PARSER_H
