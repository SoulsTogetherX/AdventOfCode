#include "Point2D.h"
#include <string>
#include <cmath>


template <typename T>
Point2D<T>::Point2D() : x(), y() {};
template <typename T>
Point2D<T>::Point2D(const T& val) : x(val), y(val) {};
template <typename T>
Point2D<T>::Point2D(const T& x_coord, const T& y_coord) : x(x_coord), y(y_coord) {};

template <typename T>
void Point2D<T>::assign_coordinates(const T& x_coord, const T& y_coord) {
    x = x_coord;
    y = y_coord;
};

template <typename T>
std::string Point2D<T>::to_string() const {
    return "Point2D(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}


template <typename T>
Point2D<T> Point2D<T>::abs() const {
    return Point2D<T>(x >= 0 ? x : -x, y >= 0 ? y : -y);
}
template <typename T>
T Point2D<T>::scalar(const Point2D<T>& p) const {
    return x * p.y - y * p.x;
}
template <typename T>
T Point2D<T>::dot(const Point2D<T>& p) const {
    return x * p.x + y * p.y;
}

template <typename T>
T Point2D<T>::manhattan_distance() const {
    return (x >= 0 ? x : -x) + (y >= 0 ? y : -y);
}
template <typename T>
T Point2D<T>::distance_squared() const {
    return x*x + y*y;
}
template <typename T>
double Point2D<T>::distance() const {
    return sqrt(x*x + y*y);
}


template <typename T>
double Point2D<T>::get_angle() const {
    return atan2(y, x);
}
template <typename T>
Point2D<T> Point2D<T>::apply_rotation(const double& angle) {
    assign_coordinates(
        x * cos(angle) - y * sin(angle),
        x * sin(angle) + y * cos(angle)
    );

    return *this;
}
template <typename T>
Point2D<T> Point2D<T>::rotate(const double& angle) {
    return Point2D(
        x * cos(angle) - y * sin(angle),
        x * sin(angle) + y * cos(angle)
    );
}


template <typename T>
Point2D<T> Point2D<T>::rotate_clockwise_90() {
return Point2D<T>(
        -y,
        x
    );
}
template <typename T>
Point2D<T> Point2D<T>::rotate_counterclockwise_90() {
    return Point2D<T>(
        y,
        -x
    );
}
template <typename T>
Point2D<T> Point2D<T>::rotate_180() {
    return Point2D<T>(
        -x,
        -y
    );
}


template <typename T>
Point2D<T> Point2D<T>::clamp(const Point2D<T>& min_pt, const Point2D<T>& max_pt) const {
    return Point2D<T>(
        x < min_pt.x ? min_pt.x : (x > max_pt.x ? max_pt.x : x),
        y < min_pt.y ? min_pt.y : (y > max_pt.y ? max_pt.y : y)
    );
}
template <typename T>
Point2D<T> Point2D<T>::clamp_val(const T& min_val, const T& max_val) const {
    return Point2D<T>(
        x < min_val ? min_val : (x > max_val ? max_val : x),
        y < min_val ? min_val : (y > max_val ? max_val : y)
    );
}
template <typename T>
Point2D<T> Point2D<T>::min(const Point2D<T>& pt) const {
    return Point2D<T>(
        x > pt.x ? pt.x : x,
        y > pt.y ? pt.y : y
    );
}
template <typename T>
Point2D<T> Point2D<T>::min_val(const T& val) const {
    return Point2D<T>(
        x > val ? val : x,
        y > val ? val : y
    );
}
template <typename T>
Point2D<T> Point2D<T>::max(const Point2D<T>& pt) const {
    return Point2D<T>(
        x < pt.x ? pt.x : x,
        y < pt.y ? pt.y : y
    );
}
template <typename T>
Point2D<T> Point2D<T>::max_val(const T& val) const {
    return Point2D<T>(
        x < val ? val : x,
        y < val ? val : y
    );
}

template <typename T>
bool Point2D<T>::has_infimum(const Point2D<T>& pt) const {
    return x < pt.x || y < pt.y;
}
template <typename T>
bool Point2D<T>::has_lower_bound(const Point2D<T>& pt) const {
    return x <= pt.x || y <= pt.y;
}
template <typename T>
bool Point2D<T>::has_supremum(const Point2D<T>& pt) const {
    return x > pt.x || y > pt.y;
}
template <typename T>
bool Point2D<T>::has_upper_bound(const Point2D<T>& pt) const {
    return x >= pt.x || y >= pt.y;
}


template <typename T>
Point2D<T> Point2D<T>::operator * (const T& factor) const {
    return Point2D<T>(x * factor, y * factor);
}
template <typename T>
Point2D<T> Point2D<T>::operator *= (const T& factor) {
    x *= factor;
    y *= factor;

    return *this;
}


template <typename T>
Point2D<T> Point2D<T>::operator / (const T& factor) const {
    return Point2D<T>(x / factor, y / factor);
}
template <typename T>
Point2D<T> Point2D<T>::operator /= (const T& factor) {
    x /= factor;
    y /= factor;

    return *this;
}


template <typename T>
Point2D<T> Point2D<T>::operator + (const Point2D<T>& p) const {
    return Point2D<T>(x + p.x, y + p.y);
}
template <typename T>
Point2D<T> Point2D<T>::operator += (const Point2D<T>& p) {
    x += p.x;
    y += p.y;

    return *this;
}


template <typename T>
Point2D<T> Point2D<T>::operator - (const Point2D<T>& p) const {
    return Point2D<T>(x - p.x, y - p.y);
}
template <typename T>
Point2D<T> Point2D<T>::operator -= (const Point2D<T>& p) {
    x -= p.x;
    y -= p.y;

    return *this;
}


template <typename T>
bool Point2D<T>::operator == (const Point2D<T>& p) const {
    return x == p.x && y == p.y;
}
template <typename T>
bool Point2D<T>::operator != (const Point2D<T>& p) const {
    return x != p.x || y != p.y;
}


template <typename T>
bool Point2D<T>::operator < (const Point2D<T>& p) const {
    return x < p.x || (x == p.x && y < p.y);
}
template <typename T>
bool Point2D<T>::operator <= (const Point2D<T>& p) const {
    return x <= p.x && (x != p.x || y <= p.y);
}

template <typename T>
bool Point2D<T>::operator > (const Point2D<T>& p) const {
    return x > p.x || (x == p.x && y > p.y);
}
template <typename T>
bool Point2D<T>::operator >= (const Point2D<T>& p) const {
    return x >= p.x && (x != p.x || y >= p.y);
}



template class Point2D<char>;
template class Point2D<signed char>;
template class Point2D<unsigned char>;
template class Point2D<wchar_t>;

template class Point2D<short>;
template class Point2D<int>;
template class Point2D<long>;
template class Point2D<long long>;

template class Point2D<unsigned short>;
template class Point2D<unsigned int>;
template class Point2D<unsigned long>;
template class Point2D<unsigned long long>;

template class Point2D<float>;
template class Point2D<double>;
template class Point2D<long double>;

#if defined(__cpp_char8_t)
template class Point2D<char8_t>;
#endif
#if defined(__cpp_char16_t)
template class Point2D<char16_t>;
#endif
#if defined(__cpp_char32_t)
template class Point2D<char32_t>;
#endif