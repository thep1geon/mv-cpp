#include "include/parser.h"
#include "include/err.h"
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
        i32 inner_i = 0;;
        Inst::BaseInst* inst;

        bool use_ident = false;
        bool func_inst = false;

        if (sublist[0].type != TokenType::Keyword 
            && sublist[0].type != TokenType::Label) {
            Err("Missing Instruction\n                  Maybe you meant to create a label?", 
                sublist[0].line_num,
                sublist[0].file)
                .fatal();
        }
        
        for (const Token& tok : sublist) {
            if (tok.type == TokenType::Keyword) {
                if (tok.value == "push") {
                    inst = new Inst::Push();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                } 
                else if (tok.value == "pop") {
                    inst = new Inst::Pop();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "swap") {
                    inst = new Inst::Swap();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "dupe") {
                    inst = new Inst::Dupe();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "add") {
                    inst = new Inst::Add();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "sub") {
                    inst = new Inst::Sub();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "inc") {
                    inst = new Inst::Inc();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "dec") {
                    inst = new Inst::Dec();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "jmp") {
                    inst = new Inst::Jump();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_gt") {
                    inst = new Inst::JumpGT();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_gteq") {
                    inst = new Inst::JumpGTE();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_lt") {
                    inst = new Inst::JumpLT();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_lteq") {
                    inst = new Inst::JumpLTE();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    inst->m_file = sublist[0].file;
                    inst->m_file = sublist[0].file;
                    inst->m_file = sublist[0].file;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_eq") {
                    inst = new Inst::JumpEQ();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "jmp_neq") {
                    inst = new Inst::JumpNEQ();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "mult") {
                    inst = new Inst::Multiply();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "div") {
                    inst = new Inst::Divide();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "dump") {
                    inst = new Inst::Dump();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "print") {
                    inst = new Inst::Print();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "mov") {
                    inst = new Inst::Move();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "stop") {
                    inst = new Inst::Stop();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "wait") {
                    inst = new Inst::Wait();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "size") {
                    inst = new Inst::Size();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "func") {
                    inst = new Inst::Func();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    func_inst = true;

                    bool found_ret = false;

                    usize j = i+1;

                    for (; j  < m_tokens.size(); ++j) {
                        if (m_tokens[j][0].value == "ret") {
                            found_ret = true;
                            break;
                        }
                        else if (m_tokens[j][0].value == "func" 
                            && !found_ret) {
                            Err("Func missing return found func instead", 
                                tok.line_num,
                                sublist[0].file)
                                .fatal();
                        }
                    }

                    if (found_ret) {
                        inst->m_operand_1 = j;
                    } else {
                        Err("Func missing return end of file found instead", 
                            tok.line_num,
                            sublist[0].file)
                            .fatal();
                    }
                }
                else if (tok.value == "call") {
                    inst = new Inst::Call();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "ret") {
                    inst = new Inst::Ret();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "read") {
                    inst = new Inst::Read();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "write") {
                    inst = new Inst::Write();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "str") {
                    inst = new Inst::Str();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "arr") {
                    inst = new Inst::Arr();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
                else if (tok.value == "include") {
                    inst = new Inst::Include();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                    use_ident = true;
                }
                else if (tok.value == "input") {
                    inst = new Inst::Input();
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }
            } 
            else if (tok.type == TokenType::Int_Lit) {
                if (inst->m_operand_1.has_value()) {
                    if (sublist[inner_i - 1].type == TokenType::Dot_Op) {
                        inst->m_operand_1.set_value(atoi(tok.value.c_str()));
                    } else {
                        inst->m_operand_2.set_value(atoi(tok.value.c_str()));
                    }
                } else if (!inst->m_operand_1.has_value()){
                    if (sublist[inner_i - 1].type == TokenType::Dot_Op) {
                        inst->m_operand_2.set_value(atoi(tok.value.c_str()));
                    } else {
                        inst->m_operand_1.set_value(atoi(tok.value.c_str()));
                    }
                }
            }
            else if (tok.type == TokenType::Str_Lit ||
                    use_ident) {
                inst->m_literal = tok.value;
            }
            else if (tok.type == TokenType::Label) {
                if (!use_ident && !func_inst) {
                    inst = new Inst::LabelInst();                 
                    inst->m_line_num = sublist[0].line_num;
                    inst->m_file = sublist[0].file;
                }

                inst->m_literal = tok.value;
                mv.m_label_table[tok.value] = Label::Label(tok.value, i);
            }
            else {
                inst = new Inst::BaseInst;
            }

            inner_i++;
        }

        m_program.push_back(inst);
        i++;
    }

    return m_program;
}
