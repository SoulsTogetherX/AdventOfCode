#include <string>
#include <cmath>

#ifndef __RANGE__HEADER__
#define __RANGE__HEADER__


template <typename T = int>
class Range {
    private:
        T st, ed;
    public:
        Range();
        Range(const T& st, const T& ed);

        std::string to_string() const;

        void assign_range(const T&, const T&);
        T get_lower() const;
        T get_upper() const;

        T size() const;

        bool includes(const T&) const;
        bool intersects(const Range<T>&) const;
        bool bordering(const Range<T>&) const;
        bool encompass(const Range<T>&) const;

        bool self_union(const Range<T>&);
        Range<T> union_range(const Range<T>&) const;
        Range<T> force_union_range(const Range<T>&) const;

        bool separate_subtracts(const Range<T>&) const;
        Range<T> subtract_range_min(const Range<T>&) const;
        Range<T> subtract_range_max(const Range<T>&) const;

        bool similar(const Range<T>&) const;
        bool operator == (const Range<T>&) const;
        bool operator != (const Range<T>&) const;

        bool operator < (const Range<T>&) const;
        bool operator <= (const Range<T>&) const;

        bool operator > (const Range<T>&) const;
        bool operator >= (const Range<T>&) const;

        template <typename T2>
        friend std::ostream& operator<<(std::ostream&, const Range<T2>&);
};



template <typename T = int>
std::ostream& operator<<(std::ostream& os, const Range<T>& r) {
    os << r.to_string();
    return os;
}

#endif