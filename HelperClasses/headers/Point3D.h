#include <string>

#ifndef __POINT_3D__HEADER__
#define __POINT_3D__HEADER__


template <typename T = int>
class Point3D{
    public:
        T x, y, z;

        Point3D();
        Point3D(const T&);
        Point3D(const T&, const T&, const T&);

        void assign_coordinates(const T&, const T&, const T&);

        std::string to_string() const;

        Point3D<T> abs() const;
        Point3D<T> cross_product(const Point3D<T>&) const;
        T dot(const Point3D<T>&) const;

        T manhattan_distance() const;
        T distance_squared() const;
        double distance() const;

        double get_angle_to(const Point3D<T>&) const;

        Point3D<T> clamp(const Point3D<T>&, const Point3D<T>&) const;
        Point3D<T> clamp_val(const T&, const T&) const;
        Point3D<T> min(const Point3D<T>&) const;
        Point3D<T> min_val(const T&) const;
        Point3D<T> max(const Point3D<T>&) const;
        Point3D<T> max_val(const T&) const;

        bool has_infimum(const Point3D<T>&) const;
        bool has_lower_bound(const Point3D<T>&) const;
        bool has_supremum(const Point3D<T>&) const;
        bool has_upper_bound(const Point3D<T>&) const;

        Point3D<T> operator * (const T&) const;
        Point3D<T> operator *= (const T&);

        Point3D<T> operator / (const T&) const;
        Point3D<T> operator /= (const T&);

        Point3D<T> operator + (const Point3D<T>&) const;
        Point3D<T> operator += (const Point3D<T>&);

        Point3D<T> operator - (const Point3D<T>&) const;
        Point3D<T> operator -= (const Point3D<T>&);

        bool operator == (const Point3D<T>&) const;
        bool operator != (const Point3D<T>&) const;

        bool operator < (const Point3D<T>&) const;
        bool operator <= (const Point3D<T>&) const;

        bool operator > (const Point3D<T>&) const;
        bool operator >= (const Point3D<T>&) const;

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const Point3D<T2>&);
};



template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Point3D<T>& pt) {
    os << pt.to_string();
    return os;
}

#endif