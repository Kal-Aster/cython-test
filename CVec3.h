#ifndef __C_VEC3_H__
#define __C_VEC3_H__

#include <math.h>

class CVec3 {
  public:
    CVec3(
      float _x, float _y, float _z
    ): x(_x), y(_y), z(_z) {}

    float x, y, z;

    CVec3* clone() const {
      return new CVec3(this->x, this->y, this->z);
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
    static CVec3* cross(
      const CVec3* v1,
      const CVec3* v2
    ) {
      return v1->clone()->cross(v2);
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
    static CVec3* add(
      const CVec3* v1,
      const CVec3* v2
    ) {
      return v1->clone()->add(v2);
    }
};

#endif