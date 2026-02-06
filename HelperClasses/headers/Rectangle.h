#include <string>

#ifndef __RECTANGLE__HEADER__
#define __RECTANGLE__HEADER__


#pragma region Class Definition
template <typename T = int>
class Rectangle {
    public:
        T x, y, width, height;

        Rectangle();
        Rectangle(const T&, const T&, const T&, const T&);
        Rectangle(const std::pair<T, T>&, const std::pair<T, T>&);
        Rectangle(const std::initializer_list<T>&);
        Rectangle(const Rectangle<T>&);

        std::string to_string() const;

        void assign_position(const T&, const T&);
        void assign_position(const std::pair<T, T>&);
        void assign_position(const std::initializer_list<T>&);
        void assign_position(const Rectangle<T>&);

        void assign_dimensions(const T&, const T&);
        void assign_dimensions(const std::pair<T, T>&);
        void assign_dimensions(const std::initializer_list<T>&);
        void assign_dimensions(const Rectangle<T>&);

        void assign_rectangle(const T&, const T&, const T&, const T&);
        void assign_rectangle(const std::pair<T, T>&, const std::pair<T, T>&);
        void assign_rectangle(const std::initializer_list<T>&);
        void assign_rectangle(const Rectangle<T>&);

        std::pair<T, T> unpack_position() const;
        std::pair<T, T> unpack_dimensions() const;

        Rectangle<T> abs() const;

        bool encloses(const Rectangle<T>&) const;
        Rectangle<T> merge(const Rectangle<T>&) const;
        
        Rectangle<T> intersection(const Rectangle<T>&) const;
        bool intersects(const Rectangle<T>&, const bool& = false) const;

        Rectangle<T> expand(const T&, const T&) const;
        Rectangle<T> expand(const std::pair<T, T>&) const;

        double get_area() const;
        std::pair<T, T> get_center() const;
        std::pair<T, T> get_end() const;

        bool has_area() const;
        bool has_point(const T&, const T&) const;
        bool has_point(const std::pair<T, T>&) const;
        
        Rectangle<T>& operator = (const std::initializer_list<T>&);

        bool operator ! () const;

        bool operator == (const Rectangle<T>&) const;
        bool operator != (const Rectangle<T>&) const;

        explicit operator bool() const;
        explicit operator std::string() const;
        template <typename T2>
        operator Rectangle<T2>() const;

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const Rectangle<T2>&);
        template<typename T2>
        friend std::istream& operator>>(std::istream&, const Rectangle<T2>&);
};
#pragma endregion


#pragma region Stream Methods
template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rect) {
    os << rect.to_string();
    return os;
}
template <typename T = int>
std::istream& operator>>(std::istream& is, Rectangle<T>& rect) {
    is >> rect.x >> rect.y >> rect.width >> rect.height;
    return is;
}
#pragma endregion


#pragma region Hashing
namespace std {
    template <typename T>
    struct hash<Rectangle<T>> {
        std::size_t operator()(const Rectangle<T>& pt) const noexcept {
            // DJB2 Algorithm
            std::size_t hash = 5381;
            hash ^= std::hash<T>{}(pt.x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.width) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= std::hash<T>{}(pt.height) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

            return hash;
        }
    };
}
#pragma endregion

#endif