#include "include/label.h"
#include "include/types.h"
#include <string>

namespace Label {
Label::Label() {
    m_name = "";
    m_jump_point = 0;
}

Label::Label(std::string name, usize jump_point) {
    m_name = name;
    m_jump_point = jump_point;
}
}
