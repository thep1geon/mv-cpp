#include "include/lexer.h"
#include "include/inst.h"
#include "include/result.h"
#include <cctype>
#include <string>
#include <fstream>
#include <vector>

Lexer::Lexer() {
    m_cursor = 0;
    m_line_number = 0;
    m_tokens = std::vector<std::vector<Token>>();
    m_file_path = ""; 
}

Lexer::Lexer(const char* filepath) {
    m_cursor = 0;
    m_line_number = 0;
    m_tokens = std::vector<std::vector<Token>>();

    m_file_path = filepath; 

    m_file.open(m_file_path);

    if (!m_file.is_open()) {
        Err("File: " + m_file_path + " not found").fatal();
    }
}

Lexer::~Lexer() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

void Lexer::set_file(const char* filepath) {
    m_file.open(filepath); 
    m_file_path = filepath;
}

Result<char> Lexer::peek(usize offset) {
    if (m_cursor + offset < m_line.length()) {
        return m_line[m_cursor+offset];
    }

    return Err("Lexer::peek: offset out of bounds");
}

char Lexer::consume() {
    return m_line[m_cursor++];
}

std::vector<Token> Lexer::tokenize_line(i32 line_num) {
    std::vector<Token> tokens = std::vector<Token>(); 
    std::string buf;

    while (peek().is_ok()) {
        if (std::isalpha(peek().get_ok())) {
            buf.push_back(consume());

            while (peek().is_ok() && (std::isalnum(peek().get_ok())||peek().get_ok() == '_')) {
                buf.push_back(consume());
            }


            std::string inst = Inst::inst_map_str[buf];
            Token tok = Token();
            tok.line_num = line_num;
            tok.file = m_file_path;


            if (inst == "") {
                tok.type = TokenType::Ident;
            } else {
                tok.type = TokenType::Keyword;
            }

            if (peek().is_ok() && peek().get_ok() == ':') {
                consume();
                tok.type = TokenType::Label;
            }

            tok.value = buf;
            buf.clear();
            
            tokens.push_back(tok);
        }
        else if (std::isdigit(peek().get_ok())) {
            buf.push_back(consume());

            while (peek().is_ok() && std::isdigit(peek().get_ok())) {
                buf.push_back(consume());
            }

            tokens.push_back(Token(TokenType::Int_Lit, buf, line_num, m_file_path));
            buf.clear();
        }
        else if (peek().get_ok() == '"' || peek().get_ok() == '\'') {
            m_cursor++;
            while (peek().is_ok() && peek().get_ok() != '"' && peek().get_ok() != '\'') {
                if (peek().get_ok() == '\\') {
                    consume();
                    if (peek().is_ok()) {
                        switch (peek().get_ok()) {
                            case 'n':  consume(); buf.push_back('\n'); break;
                            case 't':  consume(); buf.push_back('\t'); break;
                            case 'r':  consume(); buf.push_back('\r'); break;
                            case '\\': consume(); buf.push_back('\\'); break;
                            case 'b':  consume(); buf.push_back('\b'); break;
                            case '\'':  consume(); buf.push_back('\''); break;
                            case '\"':  consume(); buf.push_back('\"'); break;
                            default: Err("Lexer: Unknown Escape Character", line_num, m_file_path).fatal();
                        }
                    } else {
                        buf.push_back('\\');
                    }
                } else {
                    buf.push_back(consume());
                }
            }  

            if (peek().is_err()) {
                Err("Lexer: Missing Ending Quotes", line_num, m_file_path).fatal();
            }

            if (peek().get_ok() == '"' || peek().get_ok() == '\'') {
                m_cursor++;
            }

            tokens.push_back(Token(TokenType::Str_Lit, buf, line_num, m_file_path));
            buf.clear();
        }
        else if (peek().get_ok() == '#' || peek().get_ok() == ';') {
            break;
        }
        else if (peek().get_ok() == '.') {
            buf.push_back(consume());

            if (peek().is_ok() && peek().get_ok() == '.') {
                buf.push_back(consume());
            }

            tokens.push_back(Token(TokenType::Dot_Op, buf, line_num, m_file_path));
            buf.clear();
        }
        else if (peek().get_ok() == '|') {
            consume();
            tokens.push_back(Token(TokenType::Pipe_Op, "|", line_num, m_file_path));
            buf.clear();
        }
        else if (peek().get_ok() == '-') {
            consume();
            while (peek().is_ok() && std::isdigit(peek().get_ok())) {
                buf.push_back(consume());
            }

            i32 num = std::stoi(buf);
            num *= -1;

            tokens.push_back(Token(TokenType::Int_Lit, std::to_string(num), line_num, m_file_path));
            buf.clear();
        }
        else if (std::isspace(peek().get_ok()) || std::isblank(peek().get_ok())) {
            consume();
        }
        else {
            std::cout << m_line[m_cursor] << "\n";
            Err("Lexer: Unknown character", line_num, m_file_path).fatal();
        }
    }

    m_cursor = 0;
    return tokens;
}

std::vector<std::vector<Token>> Lexer::tokenize_file() {
    if (!m_file.is_open()) {
        Err("Lexer tokenize_file(): File not opened").fatal();
    }

    Result<char> c;
    i32 line = 0;

    while (std::getline(m_file, m_line)) {
        std::vector<Token> tokens = tokenize_line(++line);
        
        if (tokens.size() > 0) {
            m_tokens.push_back(tokens);
        }

    }

    return m_tokens;
}
