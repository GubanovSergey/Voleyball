#include "vector2D.h"
#include <iostream>
#include <cstdlib>

class Line_segment;
class Circle;
class Rectangle;

class Shape {
protected:
	typedef Vector2D Vector;
	Vector coord_;
public:
	explicit Shape(const Vector & coord):
		coord_(coord) {}
    const Vector & tell_coord() const{
		return coord_;
	}
	bool is_intersect(const Shape & rhs) const {
		return rhs.is_intersect(*this);
	}
	virtual bool is_intersect(const Rectangle &) const = 0;
	virtual bool is_intersect(const Circle &) const = 0;
	virtual bool is_intersect(const Line_segment &) const = 0;
	virtual ~Shape() {}

    struct Points_array;
};

struct Line_segment: public Shape {
protected:
	Vector coord2_;
	friend void to_coordinates(Line_segment *, Circle *);
private:
    bool involve (const Vector & point) const{
        auto mod = module(coord2_ - coord_);
        if (module (point - coord_) > mod)
            return false;
        return (module(point - coord2_) <= mod);
    }

    bool along_line (const Line_segment & rhs) const{
        if (rhs.involve(coord_))
            return true;
        return rhs.involve(coord2_);
    }

public:
    const Vector & tell_coord2() const{
		return coord_;
	}
	explicit Line_segment (const Vector & start, const Vector & end):
		Shape(start), coord2_(end) {}
	bool is_intersect (const Line_segment & rhs) const;
	bool is_intersect (const Circle & rhs) const;
	bool is_intersect (const Rectangle & rhs) const;
};

class Circle: public Shape {
protected:
	Vector::DimType radius_;
	friend void to_coordinates(Line_segment *, Circle *);
	friend void to_coordinates(Rectangle *, Circle *);
public:
	explicit Circle(const Vector & coord, const Vector::DimType radius):
		Shape(coord), radius_(radius) {}

	bool is_intersect(const Rectangle & rhs) const;
	bool is_intersect (const Line_segment & rhs) const {
		return rhs.is_intersect(*this);
	}
	Vector::DimType tell_radius() {
	    return radius_;
	}
	bool is_intersect (const Circle & rhs) const {
		return (module (coord_ - rhs.coord_) > (radius_ + rhs.radius_)) ? false : true;
	}
};

class Rectangle: public Shape {
protected:
	//coordinates of vertice
	Vector direct_vect_;	//from coord through left side looking inside the figure
	Vector::DimType width_;
/*inline void rect_print () const {
	using std::cout;
    Vector tmp = Vector(direct_vect_.get_coord(1), -direct_vect_.get_coord(0)) * (width_ / module(direct_vect_));
    coord_.log_vector(cout);
    (coord_ + direct_vect_).log_vector(cout);
    (coord_ + tmp).log_vector(cout);
    (coord_ + tmp + direct_vect_).log_vector(cout);
}*/
public:
	const Vector & tell_direct_vect() const {
		return direct_vect_;
	}
	const Vector::DimType tell_width() const {
		return width_;
	}

	explicit Rectangle(const Vector & coord, const Vector & direct_vect = Vector (1, 0),  Vector::DimType width = 1):
		Shape(coord), direct_vect_ (direct_vect), width_(width) {}
	bool is_intersect (const Rectangle & rhs) const;
	inline bool is_intersect (const Line_segment & rhs) const;

	bool is_intersect (const Circle & rhs) const;

	friend void to_coordinates(Rectangle *, Rectangle *);
	friend void to_coordinates(Rectangle *, Circle *);
};

struct Shape::Points_array  {
private:
    unsigned len_;
    Vector * data_;
public:
    Points_array (const Rectangle & init):
    len_(4),
    data_((Vector *)std::malloc(sizeof(Vector) * 4)) {
        const Vector & dir = init.tell_direct_vect();
        Vector tmp = Vector(dir.get_coord(1), -dir.get_coord(0)) * (init.tell_width() / module(dir));
        data_[0] = init.tell_coord();
        data_[1] = data_[0] + dir;
        data_[3] = data_[0] + tmp;
        data_[2] = data_[3] + dir;
    }
    ~Points_array () {
        std::free (data_);
    }
    Points_array (Points_array & init):
    len_(init.len_),
    data_((Vector *)std::malloc(sizeof(Vector) * init.len_)) {
        for (int i = 0; i < len_; i++) {
            data_[i] = init.data_[i];
        }
    }
    const Vector & operator [] (unsigned which) const {
        assert(("Out of array of points", (which < len_)));
        return data_[which];
    }
    void log_points (std::ostream & out, char sep = ' ', char lines = '\n', char ender = '\n') const {
        for (int i = 0; i < len_; i++) {
            data_[i].log_vector(out, sep, lines);
        }
        out << ender;
        out.flush();
    }
    Points_array & operator = (const Points_array && rhs) = delete;
};

bool prelim_check(const Rectangle &, const Shape::Points_array &, bool *);

bool Circle::is_intersect(const Rectangle & rhs) const {
	return rhs.is_intersect(*this);
}
bool Line_segment::is_intersect (const Rectangle & rhs) const {
	return rhs.is_intersect(*this);
}

inline bool Rectangle::is_intersect (const Line_segment & rhs) const {
	Points_array points(*this);
	bool ans = false;
	for (int i = 0; i < 4 && !ans; i++) {
		ans |= rhs.is_intersect(Line_segment(points[i], points[(i + 1) % 4]));
	}
	return ans;
}
