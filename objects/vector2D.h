#ifndef _VECTOR_2D_
#define _VECTOR_2D_

#include <cmath>
#include <assert.h>
#include <iostream>

class Vector2D {
public:
	typedef double DimType;
	bool operator == (const Vector2D & rhs) {
		Vector2D tmp(rhs);
		tmp -= *this;
		return (tmp.x_ == 0 && tmp.y_ == 0);
	}
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

	Vector2D operator -() const {
		return Vector2D(-x_, -y_);
	}
    Vector2D & operator += (const Vector2D & rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

	Vector2D & operator -= (const Vector2D & rhs) {
		x_ -= rhs.x_;
		if (std::abs(x_) < precision)
			x_ = 0;
		y_ -= rhs.y_;
		if (std::abs(y_) < precision)
			y_ = 0;
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

	DimType vect_mult_num (const Vector2D & rhs) const {
		return x_ * rhs.y_ - y_ * rhs.x_;
	}

	void log_vector(std::ostream & out, char sep = ' ', char ender = '\n') const {
	    out << x_ << sep << y_ << ender;
	}
};


static inline Vector2D operator * (const Vector2D & vect, double k) {
	return (Vector2D(vect) *= k);
}

static inline Vector2D operator + (const Vector2D & lhs, const Vector2D & rhs) {
	return (Vector2D(lhs) += rhs);
}

static inline Vector2D operator - (const Vector2D & lhs, const Vector2D & rhs) {
	return (Vector2D(lhs) -= rhs);
}

static inline Vector2D::DimType module (const Vector2D & lhs) {
	return sqrt(lhs.scalar_mult(lhs));
}

static inline Vector2D::DimType distance(const Vector2D & lhs, const Vector2D & rhs) {
	return module(lhs - rhs);
}

#endif	//_VECTOR_2D_
