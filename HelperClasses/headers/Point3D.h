#include <string>

#ifndef __POINT_3D__HEADER__
#define __POINT_3D__HEADER__


#pragma region Class Definition
template <typename T = int>
class Point3D{
    public:
    public:
        T x, y, z;

        Point3D();
        Point3D(const T&);
        Point3D(const T&, const T&, const T&);
        Point3D(const std::initializer_list<T>&);
        template <typename T2>
        Point3D(const Point3D<T2>&);
        
        std::string to_string() const;

        void assign_coordinates(const T&, const T&, const T&);
        void assign_coordinates(const std::initializer_list<T>&);
        template <typename T2>
        void assign_coordinates(const Point3D<T2>&);

        Point3D<T> abs() const;
        Point3D<T> cross(const Point3D<T>&) const;
        T dot(const Point3D<T>&) const;

        Point3D<T> normalize() const;
        Point3D<T> interpolate(const Point3D<T>& other, const double& t) const;

        T manhattan_distance() const;
        T distance_squared() const;
        double distance() const;

        double angle_to(const Point3D<T>&) const;

        double projected_x_angle() const;
        double projected_y_angle() const;
        double projected_z_angle() const;

        Point3D<T> apply_x_axis_rotation(const double& angle);
        Point3D<T> apply_y_axis_rotation(const double& angle);
        Point3D<T> apply_z_axis_rotation(const double& angle);

        Point3D<T> x_axis_rotate(const double& angle) const;
        Point3D<T> y_axis_rotate(const double& angle) const;
        Point3D<T> z_axis_rotate(const double& angle) const;

        Point3D<T> clamp(const Point3D<T>&, const Point3D<T>&) const;
        Point3D<T> clamp_val(const T&, const T&) const;
        Point3D<T> min(const Point3D<T>&) const;
        Point3D<T> min_val(const T&) const;
        Point3D<T> max(const Point3D<T>&) const;
        Point3D<T> max_val(const T&) const;

        bool componentwise_greater(const Point3D<T>&) const;
        bool componentwise_greater_equal(const Point3D<T>&) const;
        bool componentwise_less(const Point3D<T>&) const;
        bool componentwise_less_equal(const Point3D<T>&) const;

        template <typename T2>
        Point3D<T>& operator = (const T2&);
        Point3D<T>& operator = (const std::initializer_list<T>&);

        Point3D<T> operator + (const T&) const;
        Point3D<T> operator + (const Point3D<T>&) const;
        template<typename T2>
        friend Point3D<T2> operator + (const T2&, const Point3D<T2>&);

        Point3D<T>& operator += (const T&);
        Point3D<T>& operator += (const Point3D<T>&);

        Point3D<T> operator - (const T&) const;
        Point3D<T> operator - (const Point3D<T>&) const;
        template<typename T2>
        friend Point3D<T2> operator - (const T2&, const Point3D<T2>&);

        Point3D<T>& operator -= (const T&);
        Point3D<T>& operator -= (const Point3D<T>&);

        Point3D<T> operator * (const T&) const;
        Point3D<T> operator * (const Point3D<T>&) const;
        template<typename T2>
        friend Point3D<T2> operator * (const T2&, const Point3D<T2>&);

        Point3D<T>& operator *= (const T&);
        Point3D<T>& operator *= (const Point3D<T>&);

        Point3D<T> operator / (const T&) const;
        Point3D<T> operator / (const Point3D<T>&) const;

        Point3D<T>& operator /= (const T&);
        Point3D<T>& operator /= (const Point3D<T>&);

        bool operator ! () const;

        bool operator == (const Point3D<T>&) const;
        bool operator != (const Point3D<T>&) const;

        bool operator < (const Point3D<T>&) const;
        bool operator <= (const Point3D<T>&) const;

        bool operator > (const Point3D<T>&) const;
        bool operator >= (const Point3D<T>&) const;

        explicit operator bool() const;
        explicit operator std::string() const;
        template <typename T2>
        operator Point3D<T2>() const;

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const Point3D<T2>&);
        template<typename T2>
        friend std::istream& operator>>(std::istream&, const Point3D<T2>&);
};
#pragma endregion


#pragma region Stream Methods
template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Point3D<T>& pt) {
    os << pt.to_string();
    return os;
}
template <typename T = int>
std::istream& operator>>(std::istream& is, Point3D<T>& pt) {
    is >> pt.x >> pt.y >> pt.z;
    return is;
}
#pragma endregion


#pragma region Hashing
namespace std {
    template <typename T>
    struct hash<Point3D<T>> {
        std::size_t operator()(const Point3D<T>& pt) const noexcept {
            // DJB2 Algorithm
            std::size_t hash = 5381;
            hash ^= std::hash<T>{}(pt.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

            return hash;
        }
    };
}
#pragma endregion


#endif