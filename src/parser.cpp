#include "include/parser.h"
#include "include/inst.h"
#include "include/lexer.h"
#include "include/mv.h"
#include <cstdlib>
#include <vector>

Parser::Parser(std::vector<std::vector<Token>> tokens) {
    m_tokens = tokens;
}

const std::vector<Inst::BaseInst*> Parser::parse_tokens(Mv& mv) {
    i32 i = 0;
    for (const std::vector<Token>& sublist : m_tokens) {
        Inst::BaseInst* inst;
        bool jump_inst = false; 

        if (sublist[0].type != TokenType::Keyword 
            && sublist[0].type != TokenType::Label) {
            Err("Missing Instruction").fatal();
        }
        
        for (const Token& tok : sublist) {
            if (tok.type == TokenType::Keyword) {
                if (tok.value == "push") {
                    inst = new Inst::Push();
                } 
                else if (tok.value == "pop") {
                    inst = new Inst::Pop();
                }
                else if (tok.value == "swap") {
                    inst = new Inst::Swap();
                }
                else if (tok.value == "dupe") {
                    inst = new Inst::Dupe();
                }
                else if (tok.value == "add") {
                    inst = new Inst::Add();
                }
                else if (tok.value == "sub") {
                    inst = new Inst::Sub();
                }
                else if (tok.value == "inc") {
                    inst = new Inst::Inc();
                }
                else if (tok.value == "dec") {
                    inst = new Inst::Dec();
                }
                else if (tok.value == "jmp") {
                    inst = new Inst::Jump();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_gt") {
                    inst = new Inst::JumpGT();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_gteq") {
                    inst = new Inst::JumpGTE();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_lt") {
                    inst = new Inst::JumpLT();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_lteq") {
                    inst = new Inst::JumpLTE();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_eq") {
                    inst = new Inst::JumpEQ();
                    jump_inst = true;
                }
                else if (tok.value == "jmp_neq") {
                    inst = new Inst::JumpNEQ();
                    jump_inst = true;
                }
                else if (tok.value == "mult") {
                    inst = new Inst::Multiply();
                }
                else if (tok.value == "div") {
                    inst = new Inst::Divide();
                }
                else if (tok.value == "dump") {
                    inst = new Inst::Dump();
                }
                else if (tok.value == "print") {
                    inst = new Inst::Print();
                }
                else if (tok.value == "mov") {
                    inst = new Inst::Move();
                }
                else if (tok.value == "stop") {
                    inst = new Inst::Stop();
                }
            } 
            else if (tok.type == TokenType::Int_Lit) {
                if (inst->m_operand_1.has_value()) {
                    inst->m_operand_2.set_value(atoi(tok.value.c_str()));
                } else if (!inst->m_operand_1.has_value()){
                    inst->m_operand_1.set_value(atoi(tok.value.c_str()));
                }
            }
            else if (tok.type == TokenType::Str_Lit) {
                inst->m_literal = tok.value;
            }
            else if (tok.type == TokenType::Ident) {
                if (jump_inst) {
                    inst->m_literal = tok.value;
                }
            }
            else if (tok.type == TokenType::Label) {
                inst = new Inst::LabelInst();                 
                inst->m_literal = tok.value;

                mv.m_label_table[tok.value] = Label::Label(tok.value, i);
            }
            else {
                inst = new Inst::BaseInst;
            }
        }

        m_program.push_back(inst);
        i++;
    }

    return m_program;
}
