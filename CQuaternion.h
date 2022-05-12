#ifndef __C_QUATERNION_H__
#define __C_QUATERNION_H__

#include "CMat3.h"
#include "CVec3.h"

class CQuaternion
{
  public:
    CQuaternion(
      float w, float x,float y, float z
    );

    float w, x, y, z;

    CQuaternion* clone(CQuaternion* ptr) const;

    CQuaternion* conjugate();

    float dot(
      const CQuaternion* other
    ) const;

    // exp() not implemented

    CQuaternion* reset(); // to identity

    CQuaternion* inverse();

    bool isIdentity() const;

    float length() const;

    float lengthSquared() const;

    // ln() not implemented

    CQuaternion* multiply(
      const CQuaternion* other
    );

    CQuaternion* normalize();

    CQuaternion* fromRotationAxis(
      const CVec3* axis,
      float angle
    );

    CQuaternion* fromRotationMatrix(
      const CMat3* matrix
    );

    CQuaternion* fromYawPitchRoll(
      float yaw,
      float pitch,
      float roll
    );

    static CQuaternion* slerp(
      CQuaternion* ptr,
      const CQuaternion* q1,
      const CQuaternion* q2,
      float t
    );

    void toAxisAngle(
      CVec3* pAxis,
      float* pAngle
    );

    CQuaternion* scale(
      float s
    );

    CQuaternion* assign(
      const CQuaternion* other
    );

    CQuaternion* add(
      const CQuaternion* other
    );

    CQuaternion* fromRotationBetweenVec3(
      const CVec3* vec1,
      const CVec3* vec2,
      const CVec3* fallback
    );

    CVec3* multiplyVec3(
      CVec3* ptr,
      const CVec3* v
    ) const;
}; // class CQuaternion

#endif
