#include "include/vector.h"

Vector2::Vector2(f32 x, f32 y) {
    m_x = x;
    m_y = y;
}

Vector2::Vector2() {
    m_x = 0;
    m_y = 0;
}

Vector2::~Vector2() {
    set_x(0);
    set_y(0);
}

f32 Vector2::get_x() {
    return m_x;
}
f32 Vector2::get_y() {
    return m_y;
}

void Vector2::set_x(f32 x) {
    m_x = x;
}
void Vector2::set_y(f32 y) {
    m_y = y;
}

Vector3::Vector3(f32 x, f32 y, f32 z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

Vector3::~Vector3() {
    set_x(0);
    set_y(0);
    set_z(0);
}

f32 Vector3::get_z() {
    return m_z;
}

void Vector3::set_z(f32 z) {
    m_z = z;
}
