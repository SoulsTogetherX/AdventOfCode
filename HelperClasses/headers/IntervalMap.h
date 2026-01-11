#ifndef __RANGE_MAP__HEADER__
#define __RANGE_MAP__HEADER__

#include "Range.h"
#include <string>
#include <vector>


template<typename T = int>
class IntervalMap{
    private:
        std::vector<Range<T>> ranges;

        unsigned int binary_search(const T&) const;
    public:
        std::string to_string() const;

        bool has_range(const Range<T>&) const;
        bool has_val(const T&) const;

        T lower_bound() const;
        T upper_bound() const;

        std::vector<Range<T>> get_ranges() const;

        void insert_range(const Range<T>&);
        void remove_range(const Range<T>&);

        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const IntervalMap<T2>&);
};



template <typename T = int>
std::ostream& operator<<(std::ostream& os, const IntervalMap<T>& ip) {
    std::vector<T> ranges = ip.get_ranges();
    if (ranges.empty()) {
        return os;
    }

    os << ranges[0].to_string();
    for(unsigned int i = 1; i < ranges.size(); i++) {
        os << " " + ranges[i].to_string();
    }
    return os;
}

#endif