#include <string>
#include <cmath>
#include "Rectangle.h"


#pragma region Constructors
template <typename T>
Rectangle<T>::Rectangle() : x(), y(), width(), height() {}
template <typename T>
Rectangle<T>::Rectangle(const T& x, const T& y, const T& width, const T& height) :
    x(x), y(y), width(width), height(height) {}
template <typename T>
Rectangle<T>::Rectangle(const std::pair<T, T>& position, const std::pair<T, T>& dimension) :
    x(position.first), y(position.second), width(dimension.first), height(dimension.second) {}
template <typename T>
Rectangle<T>::Rectangle(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    width = it.size() >= 3 ? *(it.begin() + 2) : 0;
    height = it.size() >= 4 ? *(it.begin() + 3) : 0;
}
template <typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& rect) {
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
}
#pragma endregion


#pragma region to_string
template <typename T>
std::string Rectangle<T>::to_string() const {
    return "Rect<(" + std::to_string(x) + ", " + std::to_string(y) + "), (" + std::to_string(width) + ", " + std::to_string(height) + ")>";
}
#pragma endregion


#pragma region Assignment Methods
template <typename T>
void Rectangle<T>::assign_position(const T& x_pos, const T& y_pos) {
    x = x_pos;
    y = y_pos;
}
template <typename T>
void Rectangle<T>::assign_position(const std::pair<T, T>& position) {
    x = position.first;
    y = position.second;
}
template <typename T>
void Rectangle<T>::assign_position(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
}
template <typename T>
void Rectangle<T>::assign_position(const Rectangle<T>& rect) {
    x = rect.x;
    y = rect.y;
}

template <typename T>
void Rectangle<T>::assign_dimensions(const T& r_width, const T& r_height) {
    width = r_width;
    height = r_height;
}
template <typename T>
void Rectangle<T>::assign_dimensions(const std::pair<T, T>& dimension) {
    width = dimension.first;
    height = dimension.second;
}
template <typename T>
void Rectangle<T>::assign_dimensions(const std::initializer_list<T>& it) {
    width = it.size() >= 1 ? *it.begin() : 0;
    height = it.size() >= 2 ? *(it.begin() + 1) : 0;
}
template <typename T>
void Rectangle<T>::assign_dimensions(const Rectangle<T>& rect) {
    width = rect.width;
    height = rect.height;
}

template <typename T>
void Rectangle<T>::assign_rectangle(const T& x_pos, const T& y_pos, const T& r_width, const T& r_height) {
    x = x_pos;
    y = y_pos;
    width = r_width;
    height = r_height;
}
template <typename T>
void Rectangle<T>::assign_rectangle(const std::pair<T, T>& position, const std::pair<T, T>& dimension) {
    x = position.first;
    y = position.second;
    width = dimension.first;
    height = dimension.second;
}
template <typename T>
void Rectangle<T>::assign_rectangle(const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    width = it.size() >= 3 ? *(it.begin() + 2) : 0;
    height = it.size() >= 4 ? *(it.begin() + 3) : 0;
}
template <typename T>
void Rectangle<T>::assign_rectangle(const Rectangle<T>& rect) {
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
}
#pragma endregion


#pragma region Misc Helper Methods
template <typename T>
std::pair<T, T> Rectangle<T>::unpack_position() const {
    return std::pair<T, T>(x, y);
}
template <typename T>
std::pair<T, T> Rectangle<T>::unpack_dimensions() const {
    return std::pair<T, T>(width, height);
}

template <typename T>
Rectangle<T> Rectangle<T>::abs() const {
    Rectangle<T> ret;

    if (width < 0) {
        ret.x = x + width;
        ret.width = -width;
    } else {
        ret.x = x;
        ret.width = width;
    }

    if (height < 0) {
        ret.y = y + height;
        ret.height = -height;
    } else {
        ret.y = y;
        ret.height = height;
    }

    return ret;
}

template <typename T>
bool Rectangle<T>::encloses(const Rectangle<T>& rect) const {
    return x <= rect.x && y <= rect.y && rect.x + rect.width <= x + width && rect.y + rect.height <= y + height;
}
template <typename T>
Rectangle<T> Rectangle<T>::merge(const Rectangle<T>& rect) const {
    std::pair<T, T> end = get_end(), rect_end = rect.get_end();

    T new_x = x <= rect.x ? x : rect.x;
    T new_y = y <= rect.y ? y : rect.y;
    T new_width = end.first <= rect_end.first ? rect_end.first - new_x : end.first - new_x;
    T new_height = end.second <= rect_end.second ? rect_end.second - new_y : end.second - new_y;

    return Rectangle<T>(
        new_x,
        new_y,
        new_width,
        new_height
    );
}
#pragma endregion


#pragma region Intersection Methods
template <typename T>
Rectangle<T> Rectangle<T>::intersection(const Rectangle<T>& rect) const {
    std::pair<T, T> end = get_end(), rect_end = rect.get_end();

    T new_x = rect.x <= x ? x : rect.x;
    T new_y = rect.y <= y ? y : rect.y;
    T new_width = rect_end.first <= end.first ? rect_end.first - new_x : end.first - new_x;
    T new_height = rect_end.second <= end.second ? rect_end.second - new_y : end.second - new_y;

    return Rectangle<T>(new_x, new_y, new_width, new_height);
}
template <typename T>
bool Rectangle<T>::intersects(const Rectangle<T>& rect, const bool& include_edges) const {
    std::pair<T, T> end = get_end(), rect_end = rect.get_end();
    // Rect<(45, 64), (22, 22)> Rect<(42, 646), (18, 20)>
    if (include_edges) {
        return (x <= rect_end.first && rect.x <= end.first && rect.y <= end.second && y <= rect_end.second);
    }
    return (x < rect_end.first && rect.x < end.first && rect.y < end.second && y < rect_end.second);
}
#pragma endregion


#pragma region Expand Methods
template <typename T>
Rectangle<T> Rectangle<T>::expand(const T& x_pos, const T& y_pos) const {
    std::pair<T, T> end = get_end();

    T new_x = x <= x_pos ? x : x_pos;
    T new_y = y <= y_pos ? y : y_pos;
    T new_width = (x_pos <= end.first ? end.first : y_pos) - new_x;
    T new_height = (y_pos <= end.second ? end.second : y_pos) - new_y;

    return Rectangle<T>(new_x, new_y, new_width, new_height);
}
template <typename T>
Rectangle<T> Rectangle<T>::expand(const std::pair<T, T>& coordinate) const {
    return expand(coordinate.first, coordinate.second);
}
#pragma endregion


#pragma region Accessor Methods
template <typename T>
double Rectangle<T>::get_area() const {
    return width * height;
}
template <typename T>
std::pair<T, T> Rectangle<T>::get_center() const {
    return std::pair<T, T>(x + width / 2, y + height / 2);
}
template <typename T>
std::pair<T, T> Rectangle<T>::get_end() const {
    return std::pair<T, T>(x + width, y + height);
}
#pragma endregion


#pragma region Check Has Methods
template <typename T>
bool Rectangle<T>::has_area() const {
    return width != 0 && height != 0;
}
template <typename T>
bool Rectangle<T>::has_point(const T& x_pos, const T& y_pos) const {
    return x <= x_pos && y <= y_pos && x_pos < x + width && y_pos <= y + height;
}
template <typename T>
bool Rectangle<T>::has_point(const std::pair<T, T>& coordinate) const {
    return has_point(coordinate.first, coordinate.second);
}
#pragma endregion


#pragma region Assignment Operator
template <typename T>
Rectangle<T>& Rectangle<T>::operator = (const std::initializer_list<T>& it) {
    x = it.size() >= 1 ? *it.begin() : 0;
    y = it.size() >= 2 ? *(it.begin() + 1) : 0;
    width = it.size() >= 3 ? *(it.begin() + 2) : 0;
    height = it.size() >= 4 ? *(it.begin() + 3) : 0;

    return *this;
}

template <typename T>
bool Rectangle<T>::operator ! () const {
    return !has_area();
}
#pragma endregion


#pragma region Comparisons Operators
template <typename T>
bool Rectangle<T>::operator == (const Rectangle<T>& rect) const {
    return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
}
template <typename T>
bool Rectangle<T>::operator != (const Rectangle<T>& rect) const {
    return x != rect.x || y != rect.y || width != rect.width || height != rect.height;
}
#pragma endregion


#pragma region Type Casting Methods
template <typename T>
Rectangle<T>::operator bool() const {
    return has_area();
}
template <typename T>
Rectangle<T>::operator std::string() const {
    return to_string();
}
template <typename T>
template <typename T2>
Rectangle<T>::operator Rectangle<T2>() const {
    return Rectangle<T2>((T2)x, (T2)y, (T2)width, (T2)height);
}
#pragma endregion


#pragma region Allowed Templates
template class Rectangle<char>;
template class Rectangle<signed char>;
template class Rectangle<unsigned char>;
template class Rectangle<wchar_t>;

template class Rectangle<short>;
template class Rectangle<int>;
template class Rectangle<long>;
template class Rectangle<long long>;

template class Rectangle<unsigned short>;
template class Rectangle<unsigned int>;
template class Rectangle<unsigned long>;
template class Rectangle<unsigned long long>;

template class Rectangle<float>;
template class Rectangle<double>;
template class Rectangle<long double>;

#if defined(__cpp_char8_t)
template class Rectangle<char8_t>;
#endif
#if defined(__cpp_char16_t)
template class Rectangle<char16_t>;
#endif
#if defined(__cpp_char32_t)
template class Rectangle<char32_t>;
#endif
#pragma endregion