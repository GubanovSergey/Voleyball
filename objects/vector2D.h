#ifndef _VECTOR_2D_
#define _VECTOR_2D_

#include <math.h>
#include <assert.h>

class Vector2D {
public:    
	typedef double DimType;
protected:
    DimType x_;
    DimType y_;
public:
	static constexpr DimType precision = 1E-06;
    explicit Vector2D (DimType x, DimType y):
        x_(x), y_(y) {}

    DimType get_coord (unsigned which) const {
        assert(which <= 1);
        if (!which)
            return x_;
        else
            return y_;
    }

	Vector2D operator -() const{
		return Vector2D(-x_, -y_);
	}
    Vector2D & operator += (const Vector2D & rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }
  
    Vector2D & operator *= (double k) {
        x_ *= k;
        y_ *= k;
        return *this;
    }
    DimType scalar_mult (const Vector2D & rhs) const {
        return x_ * rhs.x_ + y_ * rhs.y_;
    }
};

static inline int coord_diff(const Vector2D & lhs, const Vector2D & rhs, unsigned which) {
	assert(which <= 1);
	Vector2D::DimType answer = lhs.get_coord(which) - rhs.get_coord(which);
	return (answer < Vector2D::precision) ? 0 : answer;
}

static inline Vector2D operator * (const Vector2D & vect, double k) {
	return (Vector2D(vect) *= k);
}

static inline Vector2D operator + (const Vector2D & lhs, const Vector2D & rhs) {
	return (Vector2D(lhs) += rhs);
}

static inline Vector2D operator - (const Vector2D & lhs, const Vector2D & rhs) {
	return (Vector2D(lhs) += -rhs);
}

static inline Vector2D::DimType module (const Vector2D & lhs) {
	return sqrt(lhs.scalar_mult(lhs));
}

static inline Vector2D::DimType distance(const Vector2D & lhs, const Vector2D & rhs) {	//TODO DBG
	return module(lhs - rhs);
}

#endif	//_VECTOR_2D_