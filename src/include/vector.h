#ifndef __VECTOR_H
#define __VECTOR_H

#include "types.h"

class Vector2 {
protected:
    f32 m_x, m_y;
public:
    Vector2(f32 x, f32 y);
    Vector2();
    ~Vector2();
    f32 get_x();
    f32 get_y();

    void set_x(f32 x);
    void set_y(f32 y);
};

class Vector3 : public Vector2 {
protected:
    f32 m_z;
public:
    Vector3(f32 x, f32 y, f32 z);
    ~Vector3();
    f32 get_z();

    void set_z(f32 z);
};

#endif //__VECTOR_H
