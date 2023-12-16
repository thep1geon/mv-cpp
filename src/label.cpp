#include "include/label.h"
#include "include/types.h"
#include <string>
#include <iostream>

namespace Label {
Label::Label() {
    m_name = "";
    m_jump_point = 0;
}
				 
Label::Label(std::string name, usize jump_point) {
    m_name = name;
    m_jump_point = jump_point;
}

void Label::print() {
    std::cout << "Label: \n";
    std::cout << "    Jump Point: " << m_jump_point << "\n";
    std::cout << "    Name:       " << m_name << "\n";
}
}
