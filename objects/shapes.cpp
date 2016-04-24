#include "shapes.h"

bool Line_segment::is_intersect (const Line_segment & rhs) const {
    #define SIGN(x) (!!x * (!!(x > 0) * 2 - 1))
    Vector 	dir1(coord2_ - coord_),
            dir2(rhs.coord2_ - rhs.coord_);
    assert((dir1.get_coord(0) || dir1.get_coord(1)) && (dir2.get_coord(0) || dir2.get_coord(1)));
    Vector::DimType det0 = dir1.vect_mult_num(dir2);

    int mult_sign;
    bool same = true;
    auto tmp = dir1.vect_mult_num(rhs.coord2_ - coord_);
    mult_sign = SIGN(tmp);
    tmp = dir1.vect_mult_num(rhs.coord_ - coord_);
    same = (mult_sign == SIGN(tmp));
    if (same) {
        if (!mult_sign)
            return along_line(rhs);//aligned along 1 line
        return false;
    }
    same = true;

    tmp = dir2.vect_mult_num(coord2_ - rhs.coord_);
    mult_sign = SIGN(tmp);
    tmp = dir2.vect_mult_num(coord_ - rhs.coord_);
    same = (mult_sign == SIGN(tmp));
    if (same) {
        if (!mult_sign)
            return along_line(rhs);//aligned along 1 line
        return false;
    }
    return true;
    #undef SIGN
}

void to_coordinates(Rectangle * lhs, Rectangle * rhs) {
    Vector2D::DimType module1 = module(lhs->direct_vect_);
    double cos_m2 = lhs->direct_vect_.scalar_mult(rhs->direct_vect_) / module1;
    double sin_m2 = rhs->direct_vect_.vect_mult_num(lhs->direct_vect_) / module1;

    //lhs->coord_.log_vector(std::cout);
    rhs->direct_vect_ = Vector2D(sin_m2, cos_m2);
    rhs->coord_ = rhs->coord_ - lhs->coord_;

    cos_m2 = lhs->direct_vect_.scalar_mult(rhs->coord_) / module1;
    sin_m2 = rhs->coord_.vect_mult_num(lhs->direct_vect_) / module1;
    rhs->coord_ = Vector2D(sin_m2, cos_m2);

    lhs->direct_vect_ = Vector2D(0, module1);
    lhs->coord_ = Vector2D(0,0);
}

void to_coordinates(Rectangle * lhs, Circle * rhs){
    rhs->coord_ -= lhs->coord_;

    Vector2D::DimType module1 = module(lhs->direct_vect_);
    double cos_m2 = rhs->coord_.scalar_mult(lhs->direct_vect_) / module1;
    double sin_m2 = rhs->coord_.vect_mult_num(lhs->direct_vect_) / module1;
    rhs->coord_ = Vector2D(sin_m2, cos_m2);

    lhs->direct_vect_ = Vector2D(0, module1);
    lhs->coord_ = Vector2D(0,0);
}

void to_coordinates(Line_segment * lhs, Circle * rhs){
    rhs->coord_ -= lhs->coord_;

    Vector2D dir = lhs->coord2_ - lhs->coord_;
    Vector2D::DimType module1 = module(dir);
    double cos_m2 = rhs->coord_.scalar_mult(dir) / module1;
    double sin_m2 = rhs->coord_.vect_mult_num(dir) / module1;
    rhs->coord_ = Vector2D(cos_m2, sin_m2);

    lhs->coord_ = Vector2D(0,0);
    lhs->coord2_ = Vector2D(0, module1);
}

bool Line_segment::is_intersect (const Circle & rhs) const {
    Circle copied (rhs);
    Line_segment line (*this);
    Vector::DimType sum_sqr = 0, tmp = 0, tmp2 = 0;
    to_coordinates(&line, &copied);

    tmp = copied.tell_coord().get_coord(0);
    if (tmp < (tmp2 = 0) || tmp > (tmp2 = line.coord2_.get_coord(0)))
        sum_sqr += (tmp - tmp2) * (tmp - tmp2);
    tmp = copied.tell_coord().get_coord(1);
    sum_sqr += tmp * tmp;
    tmp = copied.tell_radius();
    if (sum_sqr > tmp * tmp)
        return false;
    return true;
}

bool Rectangle::is_intersect (const Circle & rhs) const {
	Circle copied (rhs);
	Vector center (copied.tell_coord());
	Vector::DimType sum_sqr = 0, tmp = 0, tmp2 = 0;
	Rectangle this_rect (*this);
	to_coordinates(&this_rect, &copied);

	tmp = copied.tell_coord().get_coord(0);
	if (tmp < (tmp2 = 0) || tmp > (tmp2 = this_rect.width_))
		sum_sqr += (tmp - tmp2) * (tmp - tmp2);
	tmp = copied.tell_coord().get_coord(1);
	if (tmp < (tmp2 = 0) || tmp > (tmp2 = this_rect.direct_vect_.get_coord(1)))
		sum_sqr += (tmp - tmp2) * (tmp - tmp2);
	tmp = copied.tell_radius();
	if (sum_sqr > tmp * tmp)
		return false;
	return true;
}

bool Rectangle::is_intersect (const Rectangle & rhs) const {
    Rectangle second = rhs;
    Rectangle first (*this);
	to_coordinates(&first, &second);
    Points_array points2(second);

    bool ans;
    if (prelim_check(first, points2, &ans))
        return ans;

    ans = false;
    for (int i = 0; i < 4 && !ans; i++) {
        Line_segment line(points2[i], points2[(i + 1) % 4]);
        ans |= first.is_intersect(line);
    }
    return ans;
}

bool prelim_check(const Rectangle &first, const Shape::Points_array & points2, bool * ans) {
    //Check if all points are on the same semi plane out of the aligned rectangle (bool same)
    //Check if all points are inside the aligned rectangle (bool same_side)
    bool same = true, same_side = true, res;
    int i;
    for (i = 0; i < 4; i++) {
        res = (points2[i].get_coord(0) < 0);
        same &= res;
        same_side &= !res;
    }
    if (same) {
        *ans = false;
        return true;
    }
    same = true;

    for (i = 0; i < 4; i++) {
        res = (points2[i].get_coord(0) > first.tell_width());
        same &= res;
        same_side &= !res;
    }
    if (same){
        *ans = false;
        return true;
    }
    same = true;

    for (i = 0; i < 4; i++) {
        res = (points2[i].get_coord(1) < 0);
        same &= res;
        same_side &= !res;
    }
    if (same){
        *ans = false;
        return true;
    }
    same = true;

    for (i = 0; i < 4; i++) {
        res = (points2[i].get_coord(1) > first.tell_direct_vect().get_coord(1));
        same &= res;
        same_side &= !res;
    }
    if (same){
        *ans = false;
        return true;
    }
    if (same_side) {
        *ans = true;
        return true;
    }
    return false;
}
