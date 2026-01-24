#include "Point3D.h"
#include <string>
#include <cmath>


template <typename T>
Point3D<T>::Point3D() : x(), y(), z() {};
template <typename T>
Point3D<T>::Point3D(const T& val) : x(val), y(val), z(val) {};
template <typename T>
Point3D<T>::Point3D(const T& x_coord, const T& y_coord, const T& z_coord) : x(x_coord), y(y_coord), z(z_coord) {};

template <typename T>
void Point3D<T>::assign_coordinates(const T& x_coord, const T& y_coord, const T& z_coord) {
    x = x_coord;
    y = y_coord;
    y = z_coord;
};

template <typename T>
std::string Point3D<T>::to_string() const {
    return "Point3D(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}


template <typename T>
Point3D<T> Point3D<T>::abs() const {
    return Point3D<T>(x >= 0 ? x : -x, y >= 0 ? y : -y, z >= 0 ? z : -z);
}
template <typename T>
Point3D<T> Point3D<T>::cross_product(const Point3D<T>& pt) const {
    return Point3D<T>(y * pt.z - z * pt.y, z * pt.x - x * pt.z, x * pt.y - y * pt.x);
}
template <typename T>
T Point3D<T>::dot(const Point3D<T>& p) const {
    return x * p.x + y * p.y;
}

template <typename T>
T Point3D<T>::manhattan_distance() const {
    return (x >= 0 ? x : -x) + (y >= 0 ? y : -y) + (z >= 0 ? z : -z);
}
template <typename T>
T Point3D<T>::distance_squared() const {
    return x*x + y*y + z*z;
}
template <typename T>
double Point3D<T>::distance() const {
    return sqrt(x*x + y*y + z*z);
}

template <typename T>
double Point3D<T>::get_angle_to(const Point3D<T>& pt) const {
    double mag1 = distance();
    double mag2 = pt.distance();

    if (mag1 == 0.0 || mag2 == 0.0) {
        return 0.0;
    }

    double dot_val = dot(pt);
    return std::acos(dot_val / (mag1 * mag2));
}

template <typename T>
Point3D<T> Point3D<T>::clamp(const Point3D<T>& min_pt, const Point3D<T>& max_pt) const {
    return Point3D<T>(
        x < min_pt.x ? min_pt.x : (x > max_pt.x ? max_pt.x : x),
        y < min_pt.y ? min_pt.y : (y > max_pt.y ? max_pt.y : y),
        z < min_pt.z ? min_pt.z : (z > max_pt.z ? max_pt.z : z)
    );
}
template <typename T>
Point3D<T> Point3D<T>::clamp_val(const T& min_val, const T& max_val) const {
    return Point3D<T>(
        x < min_val ? min_val : (x > max_val ? max_val : x),
        y < min_val ? min_val : (y > max_val ? max_val : y),
        z < min_val ? min_val : (z > max_val ? max_val : z)
    );
}
template <typename T>
Point3D<T> Point3D<T>::min(const Point3D<T>& pt) const {
    return Point3D<T>(
        x > pt.x ? pt.x : x,
        y > pt.y ? pt.y : y,
        z > pt.z ? pt.z : z
    );
}
template <typename T>
Point3D<T> Point3D<T>::min_val(const T& val) const {
    return Point3D<T>(
        x > val ? val : x,
        y > val ? val : y,
        z > val ? val : z
    );
}
template <typename T>
Point3D<T> Point3D<T>::max(const Point3D<T>& pt) const {
    return Point3D<T>(
        x < pt.x ? pt.x : x,
        y < pt.y ? pt.y : y,
        z < pt.z ? pt.z : z
    );
}
template <typename T>
Point3D<T> Point3D<T>::max_val(const T& val) const {
    return Point3D<T>(
        x < val ? val : x,
        y < val ? val : y,
        z < val ? val : z
    );
}

template <typename T>
bool Point3D<T>::has_infimum(const Point3D<T>& pt) const {
    return x > pt.x && y > pt.y && z > pt.z;
}
template <typename T>
bool Point3D<T>::has_lower_bound(const Point3D<T>& pt) const {
    return x >= pt.x && y >= pt.y && z >= pt.z;
}
template <typename T>
bool Point3D<T>::has_supremum(const Point3D<T>& pt) const {
    return x < pt.x && y < pt.y && z < pt.z;
}
template <typename T>
bool Point3D<T>::has_upper_bound(const Point3D<T>& pt) const {
    return x <= pt.x && y <= pt.y && z <= pt.z;
}


template <typename T>
Point3D<T> Point3D<T>::operator * (const T& factor) const {
    return Point3D<T>(x * factor, y * factor, z * factor);
}
template <typename T>
Point3D<T> Point3D<T>::operator *= (const T& factor) {
    x *= factor;
    y *= factor;
    z *= factor;

    return *this;
}


template <typename T>
Point3D<T> Point3D<T>::operator / (const T& factor) const {
    return Point3D<T>(x / factor, y / factor, z / factor);
}
template <typename T>
Point3D<T> Point3D<T>::operator /= (const T& factor) {
    x /= factor;
    y /= factor;
    z /= factor;

    return *this;
}


template <typename T>
Point3D<T> Point3D<T>::operator + (const Point3D<T>& p) const {
    return Point3D<T>(x + p.x, y + p.y, z + p.z);
}
template <typename T>
Point3D<T> Point3D<T>::operator += (const Point3D<T>& p) {
    x += p.x;
    y += p.y;
    z += p.z;

    return *this;
}


template <typename T>
Point3D<T> Point3D<T>::operator - (const Point3D<T>& p) const {
    return Point3D<T>(x - p.x, y - p.y, z - p.z);
}
template <typename T>
Point3D<T> Point3D<T>::operator -= (const Point3D<T>& p) {
    x -= p.x;
    y -= p.y;
    z -= p.z;

    return *this;
}


template <typename T>
bool Point3D<T>::operator == (const Point3D<T>& p) const {
    return x == p.x && y == p.y && z == p.z;
}
template <typename T>
bool Point3D<T>::operator != (const Point3D<T>& p) const {
    return x != p.x || y != p.y || z != p.z;
}


template <typename T>
bool Point3D<T>::operator < (const Point3D<T>& p) const {
    return x < p.x || (x == p.x && (y < p.y || (y == p.y && z < p.z)));
}
template <typename T>
bool Point3D<T>::operator <= (const Point3D<T>& p) const {
    return (x <= p.x && (x != p.x || (y <= p.y && (y != p.y || z <= p.z))));
}

template <typename T>
bool Point3D<T>::operator > (const Point3D<T>& p) const {
    return x > p.x || (x == p.x && (y > p.y || (y == p.y && z > p.z)));
}
template <typename T>
bool Point3D<T>::operator >= (const Point3D<T>& p) const {
    return (x >= p.x && (x != p.x || (y >= p.y && (y != p.y || z >= p.z))));
}



template class Point3D<char>;
template class Point3D<signed char>;
template class Point3D<unsigned char>;
template class Point3D<wchar_t>;

template class Point3D<short>;
template class Point3D<int>;
template class Point3D<long>;
template class Point3D<long long>;

template class Point3D<unsigned short>;
template class Point3D<unsigned int>;
template class Point3D<unsigned long>;
template class Point3D<unsigned long long>;

template class Point3D<float>;
template class Point3D<double>;
template class Point3D<long double>;

#if defined(__cpp_char8_t)
template class Point3D<char8_t>;
#endif
#if defined(__cpp_char16_t)
template class Point3D<char16_t>;
#endif
#if defined(__cpp_char32_t)
template class Point3D<char32_t>;
#endif