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

}

Lexer::Lexer(const char* filepath) {
    m_file.open(filepath);
    m_cursor = 0;
    m_line_number = 0;
    m_tokens = std::vector<std::vector<Token>>();
}

Lexer::~Lexer() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

void Lexer::set_file(const char* filepath) {
    m_file.open(filepath); 
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

std::vector<Token> Lexer::tokenize_line() {
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

            tokens.push_back(Token(TokenType::Int_Lit, buf));
            buf.clear();
        }
        else if (peek().get_ok() == '"') {
            m_cursor++;
            while (peek().is_ok() && peek().get_ok() != '"') {
                buf.push_back(consume());
            }  

            if (peek().is_err() || peek().get_ok() == '"') {
                m_cursor++;
            }

            tokens.push_back(Token(TokenType::Str_Lit, buf));
            buf.clear();
        }
        else if (peek().get_ok() == ';') {
            break;
        }
        else if (std::isspace(peek().get_ok()) || std::isblank(peek().get_ok())) {
            consume();
        }
        else {
            std::cout << m_line[m_cursor] << "\n";
            Err("Lexer: Unknown character").fatal();
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

    while (std::getline(m_file, m_line)) {
        std::vector<Token> tokens = tokenize_line();
        
        if (tokens.size() > 0) {
            m_tokens.push_back(tokens);
        }

    }

    return m_tokens;
}
