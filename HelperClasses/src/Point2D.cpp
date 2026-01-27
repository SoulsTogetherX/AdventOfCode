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
Point2D<T>::Point2D(const std::pair<T, T>& p) : x(p.first), y(p.second) {}
template <typename T>
Point2D<T>::Point2D(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
}
template <typename T>
template <typename T2>
Point2D<T>::Point2D(const Point2D<T2>& pt) : x((T)pt.x), y((T)pt.y) {}

template <typename T>
std::string Point2D<T>::to_string() const {
    return (std::string)*this;
}

template <typename T>
void Point2D<T>::assign_coordinates(const T& x_coord, const T& y_coord) {
    x = x_coord;
    y = y_coord;
}
template <typename T>
void Point2D<T>::assign_coordinates(const std::pair<T, T>& p) {
    x = p.first;
    y = p.second;
}
template <typename T>
void Point2D<T>::assign_coordinates(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
}
template <typename T>
template <typename T2>
void Point2D<T>::assign_coordinates(const Point2D<T2>& pt) {
    x = (T)pt.x;
    y = (T)pt.y;
}

template <typename T>
std::pair<T, T> Point2D<T>::unpack() const {
    return std::pair<T, T>(x, y);
}

template <typename T>
Point2D<T> Point2D<T>::abs() const {
    return Point2D<T>(x >= 0 ? x : -x, y >= 0 ? y : -y);
}
template <typename T>
T Point2D<T>::cross(const Point2D<T>& pt) const {
    return x * pt.y - y * pt.x;
}
template <typename T>
T Point2D<T>::dot(const Point2D<T>& pt) const {
    return x * pt.x + y * pt.y;
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

template<typename T>
Point2D<T> Point2D<T>::normalize() const {
    return *this / distance();
}
template<typename T>
Point2D<T> Point2D<T>::interpolate(const Point2D<T>& pt, const double& t) const {
    return *this + ((pt - *this) * t);
}

template <typename T>
double Point2D<T>::angle() const {
    return atan2(y, x);
}
template <typename T>
double Point2D<T>::angle_to(const Point2D<T>& pt) const {
    return acos(dot(pt) / (distance() * pt.distance()));
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
Point2D<T> Point2D<T>::clockwise() const {
return Point2D<T>(-y, x);
}
template <typename T>
Point2D<T> Point2D<T>::counterclockwise() const {
    return Point2D<T>(y, -x);
}
template <typename T>
Point2D<T> Point2D<T>::flip() const {
    return Point2D<T>(-x, -y);
}
template <typename T>
Point2D<T> Point2D<T>::swizzle() const {
    return Point2D<T>(x, y);
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
    return x > pt.x && y > pt.y;
}
template <typename T>
bool Point2D<T>::has_lower_bound(const Point2D<T>& pt) const {
    return x >= pt.x && y >= pt.y;
}
template <typename T>
bool Point2D<T>::has_supremum(const Point2D<T>& pt) const {
    return x < pt.x && y < pt.y;
}
template <typename T>
bool Point2D<T>::has_upper_bound(const Point2D<T>& pt) const {
    return x <= pt.x && y <= pt.y;
}

template <typename T>
template <typename T2>
Point2D<T>& Point2D<T>::operator = (const T2& val) {
    x = (T)val;
    y = (T)val;
    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator = (const std::pair<T, T>& p) {
    x = p.first;
    y = p.second;
    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator = (const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    return *this;
}

template <typename T>
Point2D<T> Point2D<T>::operator + (const T& val) const {
    return Point2D<T>(x + val, y + val);
}
template <typename T>
Point2D<T> Point2D<T>::operator + (const Point2D<T>& pt) const {
    return Point2D<T>(x + pt.x, y + pt.y);
}
template <typename T>
Point2D<T> operator + (const T& val, const Point2D<T>& pt) {
    return Point2D<T>(val + pt.x, val + pt.y);
}

template <typename T>
Point2D<T>& Point2D<T>::operator += (const T& val) {
    x += val;
    y += val;

    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator += (const Point2D<T>& pt) {
    x += pt.x;
    y += pt.y;

    return *this;
}

template <typename T>
Point2D<T> Point2D<T>::operator - (const T& val) const {
    return Point2D<T>(x - val, y - val);
}
template <typename T>
Point2D<T> Point2D<T>::operator - (const Point2D<T>& pt) const {
    return Point2D<T>(x - pt.x, y - pt.y);
}
template <typename T>
Point2D<T> operator - (const T& val, const Point2D<T>& pt) {
    return Point2D<T>(val - pt.x, val - pt.y);
}

template <typename T>
Point2D<T>& Point2D<T>::operator -= (const T& val) {
    x -= val;
    y -= val;

    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator -= (const Point2D<T>& pt) {
    x -= pt.x;
    y -= pt.y;

    return *this;
}

template <typename T>
Point2D<T> Point2D<T>::operator * (const T& val) const {
    return Point2D<T>(x * val, y * val);
}
template <typename T>
Point2D<T> Point2D<T>::operator * (const Point2D<T>& pt) const {
    return Point2D<T>(x * pt.x, y * pt.y);
}
template <typename T>
Point2D<T> operator * (const T& val, const Point2D<T>& pt) {
    return Point2D<T>(val * pt.x, val * pt.y);
}

template <typename T>
Point2D<T>& Point2D<T>::operator *= (const T& val) {
    x *= val;
    y *= val;

    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator *= (const Point2D<T>& pt) {
    x *= pt.x;
    y *= pt.y;

    return *this;
}

template <typename T>
Point2D<T> Point2D<T>::operator / (const T& val) const {
    return Point2D<T>(x / val, y / val);
}
template <typename T>
Point2D<T> Point2D<T>::operator / (const Point2D<T>& pt) const {
    return Point2D<T>(x / pt.x, y / pt.y);
}

template <typename T>
Point2D<T>& Point2D<T>::operator /= (const T& val) {
    x /= val;
    y /= val;

    return *this;
}
template <typename T>
Point2D<T>& Point2D<T>::operator /= (const Point2D<T>& pt) {
    x /= pt.x;
    y /= pt.y;

    return *this;
}

template <typename T>
bool Point2D<T>::operator ! () const {
    return x != 0 && y != 0;
}

template <typename T>
bool Point2D<T>::operator == (const Point2D<T>& pt) const {
    return x == pt.x && y == pt.y;
}
template <typename T>
bool Point2D<T>::operator != (const Point2D<T>& pt) const {
    return x != pt.x || y != pt.y;
}


template <typename T>
bool Point2D<T>::operator < (const Point2D<T>& pt) const {
    return x < pt.x || (x == pt.x && y < pt.y);
}
template <typename T>
bool Point2D<T>::operator <= (const Point2D<T>& pt) const {
    return x <= pt.x && (x != pt.x || y <= pt.y);
}

template <typename T>
bool Point2D<T>::operator > (const Point2D<T>& pt) const {
    return x > pt.x || (x == pt.x && y > pt.y);
}
template <typename T>
bool Point2D<T>::operator >= (const Point2D<T>& pt) const {
    return x >= pt.x && (x != pt.x || y >= pt.y);
}

template <typename T>
Point2D<T>::operator bool() const {
    return x != 0 || y != 0;
}
template <typename T>
Point2D<T>::operator std::string() const {
    return "Point2D(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}
template <typename T>
Point2D<T>::operator std::pair<T, T>() const {
    return std::pair<T, T>(x, y);
}
template <typename T>
template <typename T2>
Point2D<T>::operator Point2D<T2>() const {
    return Point2D<T2>((T2)x, (T2)y);
}


namespace std {
    template <typename T>
    struct hash<Point2D<T>> {
        std::size_t operator()(const Point2D<T>& pt) const noexcept {
            std::size_t h1 = std::hash<T>{}(pt.x);
            std::size_t h2 = std::hash<T>{}(pt.y);

            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
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