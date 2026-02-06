#include <string>
#include <cmath>
#include "Point3D.h"


#pragma region Constructors
template <typename T>
Point3D<T>::Point3D() : x(), y(), z() {};
template <typename T>
Point3D<T>::Point3D(const T& val) : x(val), y(val), z(val) {};
template <typename T>
Point3D<T>::Point3D(const T& x_coord, const T& y_coord, const T& z_coord) : x(x_coord), y(y_coord), z(z_coord) {};
template <typename T>
Point3D<T>::Point3D(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    z = it.size() >= 3 ? *(it.begin() + 2) : 0;
}
template <typename T>
template <typename T2>
Point3D<T>::Point3D(const Point3D<T2>& pt) : x((T)pt.x), y((T)pt.y), z((T)pt.z) {}
#pragma endregion


#pragma region to_string
template <typename T>
std::string Point3D<T>::to_string() const {
    return (std::string)*this;
}
#pragma endregion


#pragma region Assignment Methods
template <typename T>
void Point3D<T>::assign_coordinates(const T& x_coord, const T& y_coord, const T& z_coord) {
    x = x_coord;
    y = y_coord;
    z = z_coord;
}
template <typename T>
void Point3D<T>::assign_coordinates(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    z = it.size() >= 3 ? *(it.begin() + 2) : 0;
}
template <typename T>
template <typename T2>
void Point3D<T>::assign_coordinates(const Point3D<T2>& pt) {
    x = (T)pt.x;
    y = (T)pt.y;
    z = (T)pt.z;
}
#pragma endregion


#pragma region Misc Helper Methods
template <typename T>
Point3D<T> Point3D<T>::abs() const {
    return Point3D<T>(x >= 0 ? x : -x, y >= 0 ? y : -y, z >= 0 ? z : -z);
}
template <typename T>
Point3D<T> Point3D<T>::cross(const Point3D<T>& pt) const {
    return Point3D<T>(y * pt.z - z * pt.y, z * pt.x - x * pt.z, x * pt.y - y * pt.x);
}
template <typename T>
T Point3D<T>::dot(const Point3D<T>& pt) const {
    return x * pt.x + y * pt.y + z * pt.z;
}

template<typename T>
Point3D<T> Point3D<T>::normalize() const {
    return *this / distance();
}
template<typename T>
Point3D<T> Point3D<T>::interpolate(const Point3D<T>& pt, const double& t) const {
    return *this + ((pt - *this) * t);
}
#pragma endregion


#pragma region Distance Methods
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
#pragma endregion


#pragma region Rotation Methods
template <typename T>
double Point3D<T>::angle_to(const Point3D<T>& pt) const {
    return acos(dot(pt) / (distance() * pt.distance()));
}

template <typename T>
double Point3D<T>::projected_x_angle() const {
    return acos(x / distance());
}
template <typename T>
double Point3D<T>::projected_y_angle() const {
    return acos(y / distance());
}
template <typename T>
double Point3D<T>::projected_z_angle() const {
    return acos(z / distance());
}

template <typename T>
Point3D<T> Point3D<T>::apply_x_axis_rotation(const double& angle) {
    T prev_y = y, prev_z = z;
    double c = cos(angle), s = sin(angle);

    y = prev_y * c - prev_z * s;
    z = prev_y * s + prev_z * c;

    return *this;
}
template <typename T>
Point3D<T> Point3D<T>::apply_y_axis_rotation(const double& angle) {
    T prev_x = x, prev_z = z;
    double c = cos(angle), s = sin(angle);

    x = prev_x * c + prev_z * s;
    z = prev_z * c - prev_x * s;

    return *this;
}
template <typename T>
Point3D<T> Point3D<T>::apply_z_axis_rotation(const double& angle) {
    T prev_x = x, prev_y = y;
    double c = cos(angle), s = sin(angle);

    x = prev_x * c - prev_y * s;
    y = prev_y * c + prev_x * s;

    return *this;
}

template <typename T>
Point3D<T> Point3D<T>::x_axis_rotate(const double& angle) const {
    return Point3D<T>(*this).apply_x_axis_rotation(angle);
}
template <typename T>
Point3D<T> Point3D<T>::y_axis_rotate(const double& angle) const {
    return Point3D<T>(*this).apply_y_axis_rotation(angle);
}
template <typename T>
Point3D<T> Point3D<T>::z_axis_rotate(const double& angle) const {
    return Point3D<T>(*this).apply_z_axis_rotation(angle);
}
#pragma endregion


#pragma region Coordinate Limit Methods
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
#pragma endregion


#pragma region Componentwise Comparisons
template <typename T>
bool Point3D<T>::componentwise_greater(const Point3D<T>& pt) const {
    return x > pt.x && y > pt.y && z > pt.z;
}
template <typename T>
bool Point3D<T>::componentwise_greater_equal(const Point3D<T>& pt) const {
    return x >= pt.x && y >= pt.y && z >= pt.z;
}
template <typename T>
bool Point3D<T>::componentwise_less(const Point3D<T>& pt) const {
    return x < pt.x && y < pt.y && z < pt.z;
}
template <typename T>
bool Point3D<T>::componentwise_less_equal(const Point3D<T>& pt) const {
    return x <= pt.x && y <= pt.y && z <= pt.z;
}
#pragma endregion


#pragma region Assignment Operator
template <typename T>
template <typename T2>
Point3D<T>& Point3D<T>::operator = (const T2& val) {
    x = (T)val;
    y = (T)val;
    z = (T)val;
    return *this;
}
template <typename T>
Point3D<T>& Point3D<T>::operator = (const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    z = it.size() >= 2 ? *(it.begin() + 2) : 0;
    return *this;
}
#pragma endregion


#pragma region Algebra Operators
template <typename T>
Point3D<T> Point3D<T>::operator + (const T& val) const {
    return Point3D<T>(x + val, y + val, z + val);
}
template <typename T>
Point3D<T> Point3D<T>::operator + (const Point3D<T>& pt) const {
    return Point3D<T>(x + pt.x, y + pt.y, z + pt.z);
}
template <typename T>
Point3D<T> operator + (const T& val, const Point3D<T>& pt) {
    return Point3D<T>(val + pt.x, val + pt.y, val + pt.z);
}

template <typename T>
Point3D<T>& Point3D<T>::operator += (const T& val) {
    x += val;
    y += val;
    z += val;

    return *this;
}
template <typename T>
Point3D<T>& Point3D<T>::operator += (const Point3D<T>& pt) {
    x += pt.x;
    y += pt.y;
    z += pt.z;

    return *this;
}

template <typename T>
Point3D<T> Point3D<T>::operator - (const T& val) const {
    return Point3D<T>(x - val, y - val, z - val);
}
template <typename T>
Point3D<T> Point3D<T>::operator - (const Point3D<T>& pt) const {
    return Point3D<T>(x - pt.x, y - pt.y, z - pt.z);
}
template <typename T>
Point3D<T> operator - (const T& val, const Point3D<T>& pt) {
    return Point3D<T>(val - pt.x, val - pt.y, val - pt.z);
}

template <typename T>
Point3D<T>& Point3D<T>::operator -= (const T& val) {
    x -= val;
    y -= val;
    z -= val;

    return *this;
}
template <typename T>
Point3D<T>& Point3D<T>::operator -= (const Point3D<T>& pt) {
    x -= pt.x;
    y -= pt.y;
    z -= pt.z;

    return *this;
}

template <typename T>
Point3D<T> Point3D<T>::operator * (const T& val) const {
    return Point3D<T>(x * val, y * val, z * val);
}
template <typename T>
Point3D<T> Point3D<T>::operator * (const Point3D<T>& pt) const {
    return Point3D<T>(x * pt.x, y * pt.y, z * pt.z);
}
template <typename T>
Point3D<T> operator * (const T& val, const Point3D<T>& pt) {
    return Point3D<T>(val * pt.x, val * pt.y, val * pt.z);
}

template <typename T>
Point3D<T>& Point3D<T>::operator *= (const T& val) {
    x *= val;
    y *= val;
    z *= val;

    return *this;
}
template <typename T>
Point3D<T>& Point3D<T>::operator *= (const Point3D<T>& pt) {
    x *= pt.x;
    y *= pt.y;
    z *= pt.z;

    return *this;
}

template <typename T>
Point3D<T> Point3D<T>::operator / (const T& val) const {
    return Point3D<T>(x / val, y / val, z / val);
}
template <typename T>
Point3D<T> Point3D<T>::operator / (const Point3D<T>& pt) const {
    return Point3D<T>(x / pt.x, y / pt.y, z / pt.z);
}

template <typename T>
Point3D<T>& Point3D<T>::operator /= (const T& val) {
    x /= val;
    y /= val;
    z /= val;

    return *this;
}
template <typename T>
Point3D<T>& Point3D<T>::operator /= (const Point3D<T>& pt) {
    x /= pt.x;
    y /= pt.y;
    z /= pt.z;

    return *this;
}

template <typename T>
bool Point3D<T>::operator ! () const {
    return x != 0 && y != 0 && z != 0;
}
#pragma endregion


#pragma region Comparisons Operators
template <typename T>
bool Point3D<T>::operator == (const Point3D<T>& pt) const {
    return x == pt.x && y == pt.y && z == pt.y;
}
template <typename T>
bool Point3D<T>::operator != (const Point3D<T>& pt) const {
    return x != pt.x || y != pt.y || z != pt.z;
}

template <typename T>
bool Point3D<T>::operator < (const Point3D<T>& pt) const {
    return x < pt.x || (x == pt.x && (y < pt.y || (y == pt.y && z < pt.z)));
}
template <typename T>
bool Point3D<T>::operator <= (const Point3D<T>& pt) const {
    return x <= pt.x && (x != pt.x || (y <= pt.y && (y != pt.y || z <= pt.z)));
}

template <typename T>
bool Point3D<T>::operator > (const Point3D<T>& pt) const {
    return x > pt.x || (x == pt.x && (y > pt.y || (y == pt.y && z > pt.z)));
}
template <typename T>
bool Point3D<T>::operator >= (const Point3D<T>& pt) const {
    return x >= pt.x && (x != pt.x || (y >= pt.y && (y != pt.y || z >= pt.z)));
}
#pragma endregion


#pragma region Type Casting Methods
template <typename T>
Point3D<T>::operator bool() const {
    return x != 0 || y != 0 || z != 0;
}
template <typename T>
Point3D<T>::operator std::string() const {
    return "Point3D(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
template <typename T>
template <typename T2>
Point3D<T>::operator Point3D<T2>() const {
    return Point3D<T2>((T2)x, (T2)y);
}
#pragma endregion


#pragma region Allowed Templates
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

#pragma endregion