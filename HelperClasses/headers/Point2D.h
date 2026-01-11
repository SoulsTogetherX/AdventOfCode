#include <string>

#ifndef __POINT_2D__HEADER__
#define __POINT_2D__HEADER__


template <typename T = int>
class Point2D{
    public:
        T x, y;

        Point2D();
        Point2D(const T&);
        Point2D(const T&, const T&);

        void assign_coordinates(const T&, const T&);

        std::string to_string() const;

        Point2D<T> abs() const;
        T dot(const Point2D<T>&) const;
        T cross_product(const Point2D<T>&) const;

        T manhattan_distance() const;
        T distance_squared() const;
        double distance() const;

        double get_angle() const;
        Point2D<T> apply_rotation(const double&);
        Point2D<T> rotate(const double&);

        Point2D<T> clockwise_90();
        Point2D<T> counterclockwise_90();
        Point2D<T> rotate_180();

        Point2D<T> clamp(const Point2D<T>&, const Point2D<T>&) const;
        Point2D<T> clamp_val(const T&, const T&) const;
        Point2D<T> min(const Point2D<T>&);
        Point2D<T> min_val(const T&);
        Point2D<T> max(const Point2D<T>&);
        Point2D<T> max_val(const T&);

        bool axis_less(const Point2D<T>&);
        bool axis_less_equal(const Point2D<T>&);
        bool axis_greater(const Point2D<T>&);
        bool axis_greater_equal(const Point2D<T>&);

        Point2D<T> operator * (const T&) const;
        Point2D<T> operator *= (const T&);

        Point2D<T> operator / (const T&) const;
        Point2D<T> operator /= (const T&);

        Point2D<T> operator + (const Point2D&) const;
        Point2D<T> operator += (const Point2D&);

        Point2D<T> operator - (const Point2D&) const;
        Point2D<T> operator -= (const Point2D&);

        bool operator == (const Point2D<T>&) const;
        bool operator != (const Point2D<T>&) const;

        bool operator < (const Point2D<T>&) const;
        bool operator <= (const Point2D<T>&) const;

        bool operator > (const Point2D<T>&) const;
        bool operator >= (const Point2D<T>&) const;

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const Point2D<T2>&);
};



template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Point2D<T>& pt) {
    os << pt.to_string();
    return os;
}

#endif