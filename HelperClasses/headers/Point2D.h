#include <string>

#ifndef __POINT_2D__HEADER__
#define __POINT_2D__HEADER__



#pragma region Class Definition
template <typename T = int>
class Point2D{
    public:
        T x, y;

        Point2D();
        Point2D(const T&);
        Point2D(const T&, const T&);
        Point2D(const std::pair<T, T>&);
        Point2D(const std::initializer_list<T>&);
        template <typename T2>
        Point2D(const Point2D<T2>&);
        
        std::string to_string() const;

        void assign_coordinates(const T&, const T&);
        void assign_coordinates(const std::pair<T, T>&);
        void assign_coordinates(const std::initializer_list<T>&);
        template <typename T2>
        void assign_coordinates(const Point2D<T2>&);

        std::pair<T, T> unpack() const;

        Point2D<T> abs() const;
        T cross(const Point2D<T>&) const;
        T dot(const Point2D<T>&) const;

        Point2D<T> normalize() const;
        Point2D<T> interpolate(const Point2D<T>& other, const double& t) const;

        T manhattan_distance() const;
        T distance_squared() const;
        double distance() const;

        double angle_to(const Point2D<T>&) const;
        double angle() const;
        Point2D<T> apply_rotation(const double&);
        Point2D<T> rotate(const double&);

        Point2D<T> clockwise() const;
        Point2D<T> counterclockwise() const;
        Point2D<T> flip() const;
        Point2D<T> swizzle() const;

        Point2D<T> clamp(const Point2D<T>&, const Point2D<T>&) const;
        Point2D<T> clamp_val(const T&, const T&) const;
        Point2D<T> min(const Point2D<T>&) const;
        Point2D<T> min_val(const T&) const;
        Point2D<T> max(const Point2D<T>&) const;
        Point2D<T> max_val(const T&) const;

        bool componentwise_greater(const Point2D<T>&) const;
        bool componentwise_greater_equal(const Point2D<T>&) const;
        bool componentwise_less(const Point2D<T>&) const;
        bool componentwise_less_equal(const Point2D<T>&) const;

        template <typename T2>
        Point2D<T>& operator = (const T2&);
        Point2D<T>& operator = (const std::pair<T, T>&);
        Point2D<T>& operator = (const std::initializer_list<T>&);

        Point2D<T> operator + (const T&) const;
        Point2D<T> operator + (const Point2D<T>&) const;
        template<typename T2>
        friend Point2D<T2> operator + (const T2&, const Point2D<T2>&);

        Point2D<T>& operator += (const T&);
        Point2D<T>& operator += (const Point2D<T>&);

        Point2D<T> operator - (const T&) const;
        Point2D<T> operator - (const Point2D<T>&) const;
        template<typename T2>
        friend Point2D<T2> operator - (const T2&, const Point2D<T2>&);

        Point2D<T>& operator -= (const T&);
        Point2D<T>& operator -= (const Point2D<T>&);

        Point2D<T> operator * (const T&) const;
        Point2D<T> operator * (const Point2D<T>&) const;
        template<typename T2>
        friend Point2D<T2> operator * (const T2&, const Point2D<T2>&);

        Point2D<T>& operator *= (const T&);
        Point2D<T>& operator *= (const Point2D<T>&);

        Point2D<T> operator / (const T&) const;
        Point2D<T> operator / (const Point2D<T>&) const;

        Point2D<T>& operator /= (const T&);
        Point2D<T>& operator /= (const Point2D<T>&);

        bool operator ! () const;

        bool operator == (const Point2D<T>&) const;
        bool operator != (const Point2D<T>&) const;

        bool operator < (const Point2D<T>&) const;
        bool operator <= (const Point2D<T>&) const;

        bool operator > (const Point2D<T>&) const;
        bool operator >= (const Point2D<T>&) const;

        explicit operator bool() const;
        explicit operator std::string() const;
        explicit operator std::pair<T, T>() const;
        template <typename T2>
        operator Point2D<T2>() const;

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const Point2D<T2>&);
        template<typename T2>
        friend std::istream& operator>>(std::istream&, const Point2D<T2>&);
};
#pragma endregion


#pragma region Stream Methods
template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Point2D<T>& pt) {
    os << pt.to_string();
    return os;
}
template <typename T = int>
std::istream& operator>>(std::istream& is, Point2D<T>& pt) {
    is >> pt.x >> pt.y;
    return is;
}
#pragma endregion


#pragma region Hashing
namespace std {
    template <typename T>
    struct hash<Point2D<T>> {
        std::size_t operator()(const Point2D<T>& pt) const noexcept {
            // DJB2 Algorithm
            std::size_t hash = 5381;
            hash ^= std::hash<T>{}(pt.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

            return hash;
        }
    };
}
#pragma endregion


#endif