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

    CQuaternion* clone() const;

    CQuaternion* conjugate();
    static CQuaternion* conjugate(
      const CQuaternion* q
    );

    float dot(
      const CQuaternion* other
    ) const;
    static float dot(
      const CQuaternion* q1,
      const CQuaternion* q2
    );

    // exp() not implemented

    CQuaternion* reset(); // to identity

    CQuaternion* inverse();
    static CQuaternion* inverse(
      const CQuaternion* q
    );

    bool isIdentity() const;

    float length() const;

    float lengthSquared() const;

    // ln() not implemented

    CQuaternion* multiply(
      const CQuaternion* other
    );
    static CQuaternion* multiply(
      const CQuaternion* q1,
      const CQuaternion* q2
    );

    CQuaternion* normalize();
    static CQuaternion* normalize(
      const CQuaternion* q
    );

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
    static CQuaternion* scale(
      const CQuaternion* q,
      float s
    );

    CQuaternion* assign(
      const CQuaternion* other
    );

    CQuaternion* add(
      const CQuaternion* other
    );
    static CQuaternion* add(
      const CQuaternion* q1,
      const CQuaternion* q2
    );

    CQuaternion* fromRotationBetweenVec3(
      const CVec3* vec1,
      const CVec3* vec2,
      const CVec3* fallback
    );

    CVec3* multiplyVec3(
      const CVec3* v
    ) const;
    static CVec3* multiplyVec3(
      const CQuaternion* q,
      const CVec3* v
    );
}; // class CQuaternion

#endif
