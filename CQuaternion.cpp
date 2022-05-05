#define _USE_MATH_DEFINES
#include <cmath>
#include <memory.h>

#include "CQuaternion.h"

float epsilon = 1.0 / 64.0;

CQuaternion::CQuaternion(
  float _w = 1.0,
  float _x = 0.0,
  float _y = 0.0,
  float _z = 0.0
): w(_w), x(_x), y(_y), z(_z)
{};

CQuaternion* CQuaternion::clone() const {
  return new CQuaternion(
    this->w, this->x, this->y, this->z
  );
}

CQuaternion* CQuaternion::conjugate() {
  this->w = this->w;
  this->x = -this->x;
  this->y = -this->y;
  this->z = -this->z;
  
  return this;
}
CQuaternion* CQuaternion::conjugate(
  const CQuaternion* q
) {
  return q->clone()->conjugate();
}

float CQuaternion::dot(
  const CQuaternion* other
) const {
  return (
    this->w * other->w +
    this->x * other->x +
    this->y * other->y +
    this->z * other->z
  );
}
float CQuaternion::dot(
  const CQuaternion* q1,
  const CQuaternion* q2
) {
  return q1->dot(q2);
}

CQuaternion* CQuaternion::reset() {
  this->w = 1.0;
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
  
  return this;
}

CQuaternion* CQuaternion::inverse() {
  float l = this->length();
  if (abs(l) > epsilon) {
    this->w = 0.0;
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;

    return this;
  }

  return this->conjugate()->scale(1.0f / l);
}
CQuaternion* CQuaternion::inverse(
  const CQuaternion* q
) {
  return q->clone()->inverse();
}

bool CQuaternion::isIdentity() const {
  return (
    this->w == 1.0 &&
    this->x == 0.0 &&
    this->y == 0.0 &&
    this->z == 0.0
  );
}

float CQuaternion::length() const {
  return sqrt(this->lengthSquared());
}

float CQuaternion::lengthSquared() const {
  return (
    this->w * this->w +
    this->x * this->x +
    this->y * this->y +
    this->z * this->z
  );
}

// ln() not implemented

CQuaternion* CQuaternion::multiply(
  const CQuaternion* other
) {
  float w = (
    this->w * other->w -
    this->x * other->x -
    this->y * other->y -
    this->z * other->z
  );
  float x = (
    this->w * other->x +
    this->x * other->w +
    this->y * other->z -
    this->z * other->y
  );
  float y = (
    this->w * other->y +
    this->y * other->w +
    this->z * other->x -
    this->x * other->z
  );
  float z = (
    this->w * other->z +
    this->z * other->w +
    this->x * other->y -
    this->y * other->x
  );

  this->w = w;
  this->x = x;
  this->y = y;
  this->z = z;

  return this;
}
CQuaternion* CQuaternion::multiply(
  const CQuaternion* q1,
  const CQuaternion* q2
) {
  return q1->clone()->multiply(q2);
}

CQuaternion* CQuaternion::normalize() {
  float length = this->length();
  // assert(abs(length) > epsilon);
  this->scale(1.0f / length);
  
  return this;
}
CQuaternion* CQuaternion::normalize(
  const CQuaternion* q
) {
  return q->clone()->normalize();
}

CQuaternion* CQuaternion::fromRotationAxis(
  const CVec3* axis,
  float angle
) {
  float rad = angle * 0.5f;
  float scale = sin(rad);

  this->w = cos(rad);
  this->x = axis->x * scale;
  this->y = axis->y * scale;
  this->z = axis->z * scale;

  return this;
}

CQuaternion* CQuaternion::fromRotationMatrix(
  const CMat3* matrix
) {
  
  float w, x, y, z;
  float *pMatrix = NULL;
  float m4x4[16] = {0};
  float scale = 0.0f;
  float diagonal = 0.0f;

  m4x4[0]  = matrix->x1;
  m4x4[1]  = matrix->x2;
  m4x4[2]  = matrix->x3;
  m4x4[4]  = matrix->y1;
  m4x4[5]  = matrix->y2;
  m4x4[6]  = matrix->y3;
  m4x4[8]  = matrix->z1;
  m4x4[9]  = matrix->z2;
  m4x4[10] = matrix->z3;
  m4x4[15] = 1;
  pMatrix = &m4x4[0];
  
  diagonal = pMatrix[0] + pMatrix[5] + pMatrix[10] + 1;
  
  if(diagonal > epsilon) {
    // Calculate the scale of the diagonal
    scale = sqrt(diagonal) * 2;
    
    // Calculate the w, x, y and z of the quaternion through the respective equation
    w = 0.25f * scale;
    x = ( pMatrix[9] - pMatrix[6] ) / scale;
    y = ( pMatrix[2] - pMatrix[8] ) / scale;
    z = ( pMatrix[4] - pMatrix[1] ) / scale;
  } else {
    // If the first element of the diagonal is the greatest value
    if ( pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10] ) {
      // Find the scale according to the first element, and double that value
      scale = sqrt( 1.0f + pMatrix[0] - pMatrix[5] - pMatrix[10] ) * 2.0f;
      
      // Calculate the w, x, y and z of the quaternion through the respective equation
      w = (pMatrix[9] - pMatrix[6] ) / scale;
      x = 0.25f * scale;
      y = (pMatrix[4] + pMatrix[1] ) / scale;
      z = (pMatrix[2] + pMatrix[8] ) / scale;
    }
    // Else if the second element of the diagonal is the greatest value
    else if (pMatrix[5] > pMatrix[10]) {
      // Find the scale according to the second element, and double that value
      scale = sqrt( 1.0f + pMatrix[5] - pMatrix[0] - pMatrix[10] ) * 2.0f;
      
      // Calculate the w, x, y and z of the quaternion through the respective equation
      w = (pMatrix[2] - pMatrix[8] ) / scale;
      x = (pMatrix[4] + pMatrix[1] ) / scale;
      y = 0.25f * scale;
      z = (pMatrix[9] + pMatrix[6] ) / scale;
    }
    // Else the third element of the diagonal is the greatest value
    else {
      // Find the scale according to the third element, and double that value
      scale  = sqrt( 1.0f + pMatrix[10] - pMatrix[0] - pMatrix[5] ) * 2.0f;
      
      // Calculate the w, x, y and z of the quaternion through the respective equation
      w = (pMatrix[4] - pMatrix[1] ) / scale;
      x = (pMatrix[2] + pMatrix[8] ) / scale;
      y = (pMatrix[9] + pMatrix[6] ) / scale;
      z = 0.25f * scale;
    }
  }
  
  this->w = w;
  this->x = x;
  this->y = y;
  this->z = z;
  
  return this;
}

CQuaternion* CQuaternion::fromYawPitchRoll(
  float yaw,
  float pitch,
  float roll
) {
  // temp half euler angles
  float ex, ey, ez;
  // temp vars in roll,pitch yaw
  float cr, cp, cy, sr, sp, sy, cpcy, spsy;
  
  ex = pitch * 0.5f;
  ey = yaw * 0.5f;
  ez = roll * 0.5f;
  
  cr = cos(ex);
  cp = cos(ey);
  cy = cos(ez);

  sr = sin(ex);
  sp = sin(ey);
  sy = sin(ez);
  
  cpcy = cp * cy;
  spsy = sp * sy;
  
  this->w = cr * cpcy + sr * spsy;
  this->x = sr * cpcy - cr * spsy;
  this->y = cr * sp * cy + sr * cp * sy;
  this->z = cr * cp * sy - sr * sp * cy;
  
  return this->normalize();
}

CQuaternion* CQuaternion::slerp(
  const CQuaternion* q1,
  const CQuaternion* q2,
  float t
) {
  if (
    q1->w == q2->w &&
    q1->x == q2->x &&
    q1->y == q2->y &&
    q1->z == q2->z
  ) {
    return new CQuaternion(
      q1->w, q1->x, q1->y, q1->z
    );
  }

  float ct = q1->dot(q2);
  float theta = acos(ct);
  float st = sqrt(1.0f - (ct * ct));

  float stt = sin(t * theta) / st;
  float somt = sin((1.0f - t) * theta) / st;

  CQuaternion* temp1 = q1->clone()->scale(somt);
  CQuaternion* temp2 = q2->clone()->scale(stt);
  
  CQuaternion *result = CQuaternion::add(temp1, temp2);

  delete temp1, temp2;

  return result;
}

void CQuaternion::toAxisAngle(
  CVec3* axis,
  float* angle
) {
  float tempAngle = acos(this->w);
  float scale = sqrt(
    (this->x * this->x) +
    (this->y * this->y) +
    (this->z * this->z)
  );

  if (
    // angle is 0 or 360 so just simply set axis to 0,0,1 with angle 0
    (abs(scale) < epsilon) ||
    (scale < 2 * M_PI + epsilon && scale > 2 * M_PI - epsilon)
  ) {
    *angle = 0.0f;

    axis->x = 0.0f;
    axis->y = 0.0f;
    axis->z = 1.0f;

    return;
  }
  
  *angle = tempAngle * 2.0f;

  axis->x = this->x / scale;
  axis->y = this->y / scale;
  axis->z = this->z / scale;

  axis->normalize();
}

CQuaternion* CQuaternion::scale(
  float s
) {
  this->w *= s;
  this->x *= s;
  this->y *= s;
  this->z *= s;

  return this;
}
CQuaternion* CQuaternion::scale(
  const CQuaternion* q,
  float s
) {
  return q->clone()->scale(s);
}

CQuaternion* CQuaternion::assign(
  const CQuaternion* other
) {
  memcpy(this, other, sizeof(float) * 4);

  return this;
}

CQuaternion* CQuaternion::add(
  const CQuaternion* other
) {
  this->w += other->w;
  this->x += other->x;
  this->y += other->y;
  this->z += other->z;

  return this;
}
CQuaternion* CQuaternion::add(
  const CQuaternion* q1,
  const CQuaternion* q2
) {
  return q1->clone()->add(q2);
}

CQuaternion* CQuaternion::fromRotationBetweenVec3(
  const CVec3* vec1,
  const CVec3* vec2,
  const CVec3* fallback
) {
  CVec3* v1 = vec1->clone()->normalize();
  CVec3* v2 = vec2->clone()->normalize();
  float a = v1->dot(v2);

  if (a >= 1.0) {
    delete v1, v2;

    return this->reset();
  }

  if (a < (1e-6f - 1.0f))	{
    delete v1, v2;

    if (abs(fallback->lengthSquared()) < epsilon) {
      return this->fromRotationAxis(fallback, float(M_PI));
    }

    CVec3* tmp = new CVec3(1.0, 0.0, 0.0);
    CVec3* axis = CVec3::cross(tmp, vec1);

    delete tmp;

    //If axis is zero
    if (abs(axis->lengthSquared()) < epsilon) {
      axis->x = 0.0;
      axis->y = 1.0;
      axis->z = 0.0;
      
      axis->cross(vec1);
    }

    axis->normalize();
    
    this->fromRotationAxis(axis, float(M_PI));

    delete axis;

    return this;
  }
  
  float s = sqrt((1 + a) * 2);
  float invs = 1 / s;

  CVec3* c = CVec3::cross(v1, v2);
  delete v1, v2;

  this->w = s * 0.5f;
  this->x = c->x * invs;
  this->y = c->y * invs;
  this->z = c->z * invs;

  return this->normalize();
}

CVec3* CQuaternion::multiplyVec3(
  const CVec3* v
) const {
  CVec3* qvec = new CVec3(this->x, this->y, this->z);

  CVec3* uv = CVec3::cross(qvec, v);
  CVec3* uuv = CVec3::cross(qvec, uv);

  delete qvec;

  uv->scale(2.0f * this->w);
  uuv->scale(2.0f);

  uv->add(v);
  uv->add(uuv);

  delete uuv;

  return uv;
}
CVec3* CQuaternion::multiplyVec3(
  const CQuaternion* q,
  const CVec3* v
) {
  return q->multiplyVec3(v);
}