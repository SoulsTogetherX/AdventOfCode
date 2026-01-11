#include <string>
#include <cmath>
#include <iostream>
#include "Range.h"


template <typename T>
Range<T>::Range() : st(), ed() {}
template <typename T>
Range<T>::Range(const T& st_value, const T& ed_value) {
    st = st_value;
    ed = ed_value > st_value ? ed_value : st_value;
}

template <typename T>
std::string Range<T>::to_string() const {
    return "Range[" + std::to_string(st) + ", " + std::to_string(ed) + ")";
}

template <typename T>
void Range<T>::assign_range(const T& st, const T& ed) {
    this->st = st;
    this->ed = ed > st ? ed : st;
}
template <typename T>
T Range<T>::get_lower() const {
    return st;
}
template <typename T>
T Range<T>::get_upper() const {
    return ed;
}

template <typename T>
T Range<T>::size() const {
    return ed - st;
}

template <typename T>
bool Range<T>::includes(const T& val) const {
    return st <= val && val < ed;
}
template <typename T>
bool Range<T>::intersects(const Range<T>& r) const {
    return st < r.ed && r.st < ed;
}
template <typename T>
bool Range<T>::bordering(const Range<T>& r) const {
    return st == r.ed || r.st == ed;
}
template <typename T>
bool Range<T>::encompass(const Range<T>& r) const {
    return st <= r.st && ed <= r.ed;
}


template <typename T>
bool Range<T>::self_union(const Range<T>& r) {
    if (!intersects(r) && !bordering(r)) {
        return false;
    }

    st = st < r.st ? st : r.st;
    ed = ed > r.ed ? ed : r.ed;
    return true;
}
template <typename T>
Range<T> Range<T>::union_range(const Range<T>& r) const {
    if (!intersects(r) && !bordering(r)) {
        return Range();
    }

    return Range<T>(
        st < r.st ? st : r.st,
        ed > r.ed ? ed : r.ed
    );
}
template <typename T>
Range<T> Range<T>::force_union_range(const Range<T>& r) const {
    return Range<T>(
        st < r.st ? st : r.st,
        ed > r.ed ? ed : r.ed
    );
}


template <typename T>
bool Range<T>::separate_subtracts(const Range<T>& r) const {
    return st < r.st && ed < r.ed;
}
template <typename T>
Range<T> Range<T>::subtract_range_min(const Range<T>& r) const {
    if (st < r.st) {
        return Range(st, r.st);
    }
    return Range(r.ed, ed);
}
template <typename T>
Range<T> Range<T>::subtract_range_max(const Range<T>& r) const {
    if (r.ed < ed) {
        return Range(r.ed, ed);
    }
    return Range(st, r.st);
}


template <typename T>
bool Range<T>::similar(const Range<T>& r) const {
    return (*this == r) || (st == ed && r.st == r.ed);
}
template <typename T>
bool Range<T>::operator == (const Range<T>& r) const {
    return st == r.st && ed == r.ed;
}
template <typename T>
bool Range<T>::operator != (const Range<T>& r) const {
    return st != r.st || ed != r.ed;
}

template <typename T>
bool Range<T>::operator < (const Range<T>& r) const {
    return st < r.st || (st == r.st && ed < r.ed);
}
template <typename T>
bool Range<T>::operator <= (const Range<T>& r) const {
    return st < r.st || (st == r.st && ed <= r.ed);
}

template <typename T>
bool Range<T>::operator > (const Range<T>& r) const {
    return st >= r.st && (st != r.st || ed > r.ed);
}
template <typename T>
bool Range<T>::operator >= (const Range<T>& r) const {
    return st >= r.st || (st != r.st || ed >= r.ed);
}



template class Range<char>;
template class Range<signed char>;
template class Range<unsigned char>;
template class Range<wchar_t>;

template class Range<short>;
template class Range<int>;
template class Range<long>;
template class Range<long long>;

template class Range<unsigned short>;
template class Range<unsigned int>;
template class Range<unsigned long>;
template class Range<unsigned long long>;

template class Range<float>;
template class Range<double>;
template class Range<long double>;

#if defined(__cpp_char8_t)
template class Range<char8_t>;
#endif
#if defined(__cpp_char16_t)
template class Range<char16_t>;
#endif
#if defined(__cpp_char32_t)
template class Range<char32_t>;
#endif