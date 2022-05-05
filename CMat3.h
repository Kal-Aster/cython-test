#ifndef __C_MAT3_H__
#define __C_MAT3_H__

class CMat3 {
  public:
    CMat3(
      float _x1, float _y1, float _z1,
      float _x2, float _y2, float _z2,
      float _x3, float _y3, float _z3
    ):
      x1(_x1), y1(_y1), z1(_z1),
      x2(_x2), y2(_y2), z2(_z2),
      x3(_x3), y3(_y3), z3(_z3)
    {}

    float x1, y1, z1,
          x2, y2, z2,
          x3, y3, z3;
};

#endif