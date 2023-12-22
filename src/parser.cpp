#include "include/parser.h"
#include "include/arg.h"
#include "include/err.h"
#include "include/inst.h"
#include "include/lexer.h"
#include "include/mv.h"
#include <vector>

Parser::Parser(std::vector<std::vector<Token>> tokens) {
    m_tokens = tokens;
}

const std::vector<Inst::BaseInst*> Parser::parse_tokens(Mv* mv) {
    i32 i = 0;
    for (std::vector<Token>& sublist : m_tokens) {
        i32 inner_i = 0;;
        Inst::BaseInst* inst;

        bool func_inst = false;
        bool pipe_op = false;

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
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                } 
                else if (tok.value == "pop") {
                    inst = new Inst::Pop();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "swap") {
                    inst = new Inst::Swap();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "dupe") {
                    inst = new Inst::Dupe();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "add") {
                    inst = new Inst::Add();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "sub") {
                    inst = new Inst::Sub();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "inc") {
                    inst = new Inst::Inc();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "dec") {
                    inst = new Inst::Dec();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp") {
                    inst = new Inst::Jump();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_gt") {
                    inst = new Inst::JumpGT();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_gteq") {
                    inst = new Inst::JumpGTE();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_lt") {
                    inst = new Inst::JumpLT();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_lteq") {
                    inst = new Inst::JumpLTE();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_eq") {
                    inst = new Inst::JumpEQ();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "jmp_neq") {
                    inst = new Inst::JumpNEQ();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "mult") {
                    inst = new Inst::Multiply();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "div") {
                    inst = new Inst::Divide();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "dump") {
                    inst = new Inst::Dump();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "print") {
                    inst = new Inst::Print();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "mov") {
                    inst = new Inst::Move();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "stop") {
                    inst = new Inst::Stop();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "wait") {
                    inst = new Inst::Wait();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "size") {
                    inst = new Inst::Size();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "func") {
                    inst = new Inst::Func();
                    func_inst = true;
                    inst->is_func = true;
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;

                    bool found_ret = false;

                    usize j = i+1;

                    for (; j  < m_tokens.size(); ++j) {
                        if (m_tokens[j][0].value == "ret") {
                            found_ret = true;
                            break;
                        }
                        else if (m_tokens[j][0].value == "func" 
                            && !found_ret) {
                            delete inst;
                            Err("Func missing return found func instead", 
                                tok.line_num,
                                sublist[0].file)
                                .fatal();
                        }
                    }

                    if (!found_ret) {
                        delete inst;
                        Err("Func missing return EOF found instead", 
                            tok.line_num,
                            sublist[0].file)
                            .fatal();
                    }

                    inst->args.push_back(Arg(j));
                }
                else if (tok.value == "call") {
                    inst = new Inst::Call();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "ret") {
                    inst = new Inst::Ret();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "read") {
                    inst = new Inst::Read();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "write") {
                    inst = new Inst::Write();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "str") {
                    inst = new Inst::Str();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "arr") {
                    inst = new Inst::Arr();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "import") {
                    inst = new Inst::Import();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "input") {
                    inst = new Inst::Input();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "set") {
                    inst = new Inst::Set();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else if (tok.value == "del") {
                    inst = new Inst::Del();
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }
                else {
                    Err("Unknown Keyword: " + tok.value, 
                        sublist[0].line_num, sublist[0].file).fatal();
                }
            } 
            else if (tok.type == TokenType::Int_Lit) {
                inst->args.push_back(Arg(std::atoi(tok.value.c_str())));
            }
            else if (tok.type == TokenType::Str_Lit) {
                inst->args.push_back(Arg(tok.value, Arg::STR));
            }
            else if (tok.type == TokenType::Ident 
                  || tok.type == TokenType::Dot_Op) {
                inst->args.push_back(Arg(tok.value, Arg::IDENT));
            }
            else if (tok.type == TokenType::Pipe_Op) {
                pipe_op = true;

                if (inner_i + 1 > (i32)sublist.size()) {
                    Err("Parser: Pipe operator missing ident", 
                        sublist[0].line_num, sublist[0].file).fatal();
                } else if (sublist[inner_i+1].type != TokenType::Ident) {
                    Err("Parser: Pipe operator unexpected type found", 
                        sublist[0].line_num, sublist[0].file).fatal();
                }
                
                Inst::BaseInst* pop = new Inst::Pop();
                std::string ident = sublist[++inner_i].value;
                pop->args.push_back(Arg(ident, Arg::IDENT));
                pop->file = sublist[0].file;
                pop->line_num = sublist[0].line_num;

                m_program.push_back(pop);

                break;

                // str "Hello World!" | ptr
                // v v v v v v v v v v v v
                // Tok(kw, "str") Tok(str, "Hello World") Tok(P_op, "|") Tok(Id, "ptr")
                // v v v v v v v v v v v v 
                // Inst::Str() {str, "Hello World!"}
                // Inst::Pop() {ident, ptr}
            }
            else if (tok.type == TokenType::Label) {
                if (!func_inst) {
                    inst = new Inst::LabelInst();                 
                    inst->line_num = sublist[0].line_num;
                    inst->file = sublist[0].file;
                }

                inst->args.push_back(Arg(tok.value, Arg::STR));
                mv->label_table[tok.value] = Label::Label(tok.value, i);
            }
            else {
                inst = new Inst::BaseInst;
            }

            inner_i++;
        }

        if (pipe_op) {
            m_program.insert(m_program.cend()-1, inst);
        } else {
            m_program.push_back(inst);
        }

        i++;
    }

    return m_program;
}
