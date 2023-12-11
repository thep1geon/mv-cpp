#ifndef __LABEL_H
#define __LABEL_H

#include "types.h"
#include <string>
namespace Label {
struct Label {
    std::string m_name;
    usize m_jump_point;
    Label();
    Label(std::string name, usize jump_point);
};
}

#endif  //__LABEL_H
