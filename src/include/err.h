#ifndef __ERR_H
#define __ERR_H

#include <string>

enum class ErrType {
    None = 0,
    Err,
    StackOverflow,
};

class Err {
protected:
    ErrType m_type;
    std::string m_msg;
public:
    Err();
    Err(ErrType type, std::string msg);
    Err(ErrType type);
    Err(std::string msg);
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
