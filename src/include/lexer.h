#ifndef __LEXER_H
#define __LEXER_H


#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "linkedlist.h"
#include "types.h"
#include "result.h"

enum class TokenType {
    Empty = 0,
    Keyword,
    Label,
    Ident,
    Int_Lit,
    Str_Lit,
    Dot_Op,
};

struct Token {
    TokenType type;
    std::string value;
    i32 line_num;
    std::string file;

    Token(TokenType type, std::string value, i32 line_num, std::string file_path) {
        this->type = type;
        this->value = value;
        this->line_num = line_num;
        this->file = file_path;
    }

    Token() {
        type = TokenType::Empty;
        value = "";
        line_num = 0;
    }

    ~Token() = default;

    bool is_empty() const {
        return type == TokenType::Empty && value == "" && line_num == 0;
    }

    std::string type_to_str() const {
        switch (type) {
            case TokenType::Empty:   return "Empty";
            case TokenType::Keyword: return "Keyword";
            case TokenType::Ident:   return "Ident";
            case TokenType::Int_Lit: return "Int_Lit";
            case TokenType::Str_Lit: return "Str_Lit";
            default:                 return "Unknown TokenType";
        }
    }

    void print() const {
        std::cout << type_to_str() << " " << value << "\n";
    }
};

class Lexer {
    std::ifstream m_file;
    std::string m_file_path;
    usize m_cursor;  
    usize m_line_number;

    std::vector<std::vector<Token>> m_tokens;

    std::string m_line;

    Result<char> peek(usize offset = 0);
    char consume();

    std::vector<Token> tokenize_line(i32 line_num);
public:
    Lexer(const char* filepath);
    Lexer();
    ~Lexer();

    void set_file(const char* filepath);
    std::vector<std::vector<Token>> tokenize_file();
};

#endif  //__LEXER_H
