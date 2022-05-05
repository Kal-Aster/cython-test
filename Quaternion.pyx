# distutils: language = c++
# distutils: sources = CQuaternion.cpp

cdef extern from "CVec3.h":
    cdef cppclass CVec3:
        CVec3(
            float x, float y, float z
        )
        float x, y, z

cdef extern from "CMat3.h":
    cdef cppclass CMat3:
        CMat3(
            float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3
        )
        float x1, y1, z1
        float x2, y2, z2
        float x3, y3, z3

cdef extern from "CQuaternion.h":
    cdef cppclass CQuaternion:
        CQuaternion(
            float w, float x, float y, float z
        )
        float w, x, y, z
        
        CQuaternion* clone() const
        
        CQuaternion* conjugate()
        @staticmethod
        CQuaternion* conjugate(
            const CQuaternion* q
        )

        float dot(
            const CQuaternion* other
        ) const
        @staticmethod
        float dot(
            const CQuaternion* q1,
            const CQuaternion* q2
        )

        CQuaternion* reset()

        CQuaternion* inverse()
        @staticmethod
        CQuaternion* inverse(
            const CQuaternion* q
        )

        bint isIdentity() const

        float length() const

        float lengthSquared() const

        CQuaternion* multiply(
            const CQuaternion* other
        )
        @staticmethod
        CQuaternion* multiply(
            const CQuaternion* q1,
            const CQuaternion* q2
        )

        CQuaternion* normalize()
        @staticmethod
        CQuaternion* normalize(
            const CQuaternion* q
        )

        CQuaternion* fromRotationAxis(
        const CVec3* axis,
            float angle
        )

        CQuaternion* fromRotationMatrix(
            const CMat3* matrix
        )

        CQuaternion* fromYawPitchRoll(
            float yaw,
            float pitch,
            float roll
        )

        @staticmethod
        CQuaternion* slerp(
            const CQuaternion* q1,
            const CQuaternion* q2,
            float t
        )

        void toAxisAngle(
            CVec3* pAxis,
            float* pAngle
        )

        CQuaternion* scale(
            float s
        )
        @staticmethod
        CQuaternion* scale(
            const CQuaternion* q,
            float s
        )

        CQuaternion* assign(
            const CQuaternion* other
        )

        CQuaternion* add(
            const CQuaternion* other
        )
        @staticmethod
        CQuaternion* add(
            const CQuaternion* q1,
            const CQuaternion* q2
        )

        CQuaternion* fromRotationBetweenVec3(
            const CVec3* vec1,
            const CVec3* vec2,
            const CVec3* fallback
        )

        CVec3* multiplyVec3(
            const CVec3* v
        ) const
        @staticmethod
        CVec3* multiplyVec3(
            const CQuaternion* q,
            const CVec3* v
        )

cdef class Mat3:
    cdef CMat3 *_ptr

    def __cinit__(self,
        float x1 = 0.0, float y1 = 0.0, float z1 = 0.0,
        float x2 = 0.0, float y2 = 0.0, float z2 = 0.0,
        float x3 = 0.0, float y3 = 0.0, float z3 = 0.0
    ):
        self._ptr = new CMat3(
            x1, y1, z1,
            x2, y2, z2,
            x3, y3, z3
        )
        if self._ptr == NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._ptr != NULL:
            del self._ptr

cdef class Vec3:
    cdef CVec3 *_ptr

    @staticmethod
    cdef Vec3 from_ptr(CVec3 *_ptr):
        cdef Vec3 v = Vec3.__new__(Vec3)
        v._ptr = _ptr
        return v

    def __cinit__(self,
        float x = 0.0,
        float y = 0.0,
        float z = 0.0
    ):
        self._ptr = new CVec3(x, y, z)
        if self._ptr == NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._ptr != NULL:
            del self._ptr

cdef class Quaternion:
    cdef CQuaternion *_ptr
    
    @staticmethod
    cdef Quaternion from_ptr(CQuaternion *_ptr):
        cdef Quaternion q = Quaternion.__new__(Quaternion)
        q._ptr = _ptr
        return q

    def __cinit__(self,
        float w = 1.0,
        float x = 0.0,
        float y = 0.0,
        float z = 0.0
    ):
        self._ptr = new CQuaternion(w, x, y, z)
        if self._ptr == NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._ptr != NULL:
            del self._ptr

    @property
    def w(self):
        return self._ptr.w
    
    @w.setter
    def w(self, float w):
        self._ptr.w = w

    @property
    def x(self):
        return self._ptr.x
    
    @x.setter
    def x(self, float x):
        self._ptr.x = x

    @property
    def y(self):
        return self._ptr.y
    
    @y.setter
    def y(self, float y):
        self._ptr.y = y

    @property
    def z(self):
        return self._ptr.z
    
    @z.setter
    def z(self, float z):
        self._ptr.z = z
    
    def clone(self):
        cdef CQuaternion* ptr = self._ptr.clone()
        return Quaternion.from_ptr(ptr)
    
    def conjugate(self):
        self._ptr.conjugate()
        return self

    def dot(self, Quaternion other):
        return self._ptr.dot(other._ptr)

    def reset(self):
        self._ptr.reset()
        return self

    def inverse(self):
        self._ptr.inverse()
        return self

    def isIdentity(self):
        return self._ptr.isIdentity()

    def length(self):
        return self._ptr.length()

    def lengthSquared(self):
        return self._ptr.lengthSquared()

    def multiply(self, Quaternion other):
        self._ptr.multiply(other._ptr)
        return self

    def normalize(self):
        self._ptr.normalize()
        return self

    def fromRotationAxis(self, Vec3 axis, float angle):
        self._ptr.fromRotationAxis(
            axis._ptr, angle
        )
        return self

    def fromRotationMatrix(self, Mat3 matrix):
        self._ptr.fromRotationMatrix(
            matrix._ptr
        )
        return self

    def fromYawPitchRoll(self,
        float yaw,
        float pitch,
        float roll
    ):
        self._ptr.fromYawPitchRoll(yaw, pitch, roll)
        return self

    @staticmethod
    def slerp(
        Quaternion q1,
        Quaternion q2,
        float t
    ):
        cdef CQuaternion* result = CQuaternion.slerp(
            q1._ptr, q2._ptr, t
        )
        return Quaternion.from_ptr(result)

    def toAxisAngle(self):
        cdef CVec3* axis = new CVec3(0, 0, 0)
        cdef float angle
        self._ptr.toAxisAngle(axis, &angle)
        return (Vec3.from_ptr(axis), angle)

    def scale(self, float s):
        self._ptr.scale(s)
        return self

    def assign(self, Quaternion other):
        self._ptr.assign(other._ptr)
        return self

    def add(self, Quaternion other):
        self._ptr.add(other._ptr)

    def fromRotationBetweenVec3(self,
        Vec3 vec1, Vec3 vec2, Vec3 fallback
    ):
        self._ptr.fromRotationBetweenVec3(
            vec1._ptr, vec2._ptr, fallback._ptr
        )
        return self
    
    def multiplyVec3(self, Vec3 vec):
        cdef CVec3* result = self._ptr.multiplyVec3(
            vec._ptr
        )
        return Vec3.from_ptr(result)
