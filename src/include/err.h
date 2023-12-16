#ifndef __ERR_H
#define __ERR_H

#include <string>
#include "types.h"

enum class ErrType {
    None = 0,
    Err,
    StackOverflow,
};

class Err {
protected:
    ErrType m_type;
    std::string m_msg;
    i32 m_line_num;
    std::string m_file_path;
public:
    Err();
    Err(ErrType type, std::string msg);
    Err(ErrType type);
    Err(std::string msg);
    Err(std::string msg, i32 line_num);
    Err(std::string msg, i32 line_num, std::string file_path);
    ~Err();

    void fatal() const;
    void non_fatal() const;

    ErrType get_type() const;
    std::string get_msg() const;

    std::string type_to_str() const;
    void print() const;
};

#define Ok() Err(ErrType::None)

#endif  //__ERR_H
