#ifndef __C_VEC3_H__
#define __C_VEC3_H__

#include <math.h>

class CVec3 {
  public:
    CVec3(
      float _x = 0.0,
      float _y = 0.0,
      float _z = 0.0
    ): x(_x), y(_y), z(_z) {}

    float x, y, z;

    CVec3* clone(CVec3* ptr) const {
      ptr->x = this->x;
      ptr->y = this->y;
      ptr->z = this->z;

      return ptr;
    }

    float length() const {
      return sqrtf(this->lengthSquared());
    }

    float lengthSquared() const {
      return (
        this->x * this->x +
        this->y * this->y +
        this->z * this->z
      );
    }

    CVec3* normalize() {
      float length = this->length();
      
      this->x = x / length;
      this->y = y / length;
      this->z = z / length;

      return this;
    }

    float dot(
      const CVec3* other
    ) const {
      return (
        this->x * other->x +
        this->y * other->y +
        this->z * other->z
      );
    }

    CVec3* cross(
      const CVec3* other
    ) {
      float x = (this->y * other->z) - (this->z * other->y);
      float y = (this->z * other->x) - (this->x * other->z);
      float z = (this->x * other->y) - (this->y * other->x);
      
      this->x = x;
      this->y = y;
      this->z = z;

      return this;
    }

    CVec3* scale(
      float s
    ) {
      this->x *= s;
      this->y *= s;
      this->z *= s;

      return this;
    }

    CVec3* add(
      const CVec3* other
    ) {
      this->x += other->x;
      this->y += other->y;
      this->z += other->z;

      return this;
    }
};

#endif