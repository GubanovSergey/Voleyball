#include <assert.h>
#include <iostream>
#include "vector2D.h"

class Object {
protected:
    typedef Vector2D Vector;

public:
    virtual Vector::DimType get_coord (unsigned which) const = 0;
    //0 is x and 1 is y
	virtual void log_object(std::ostream & where, char ender = '\n', char sep = ' ') {
		where << get_coord(0) << sep << get_coord(1) << ender;
	}
    virtual void update (double dt) {}
    virtual ~Object () {}
};

class FixedObject: public Object {
protected:
    const Vector coord_;

public:
    FixedObject(const Vector & init_coord):
        coord_(init_coord) {}
    ~FixedObject() {}

    Vector::DimType get_coord (unsigned which) const {
        return coord_.get_coord(which);
    }
};

class MovObject: public Object {
protected:
    Vector coord_;
    Vector speed_;

public:
    MovObject(const Vector & init_coord, const Vector & init_speed = Vector(0, 0)):
        coord_(init_coord), speed_(init_speed) {}
    ~MovObject() {}

    Vector::DimType get_coord (unsigned which) const {
        return coord_.get_coord(which);
    }
    Vector::DimType get_sp_coord (unsigned which) const {
        return speed_.get_coord(which);
    }
    virtual void update(double dt) {
        coord_ += speed_ * dt;
    }
};