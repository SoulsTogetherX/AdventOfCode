#include "IntervalMap.h"
#include <string>
#include <vector>
#include <iostream>


template<typename T>
unsigned int IntervalMap<T>::binary_search(const T& target) const {
    if (ranges.empty()) {
        return 0;
    }

    int st = 0, mid, ed = ranges.size() - 1;

    while(st <= ed) {
        mid = (ed + st) / 2;

        if (ranges[mid].includes(target)) {
            return mid;
        }

        if (ranges[mid].get_upper() <= target) {
            st = mid + 1;
        } else {
            ed = mid - 1;
        }
    }

    return mid;
}



template<typename T>
std::string IntervalMap<T>::to_string() const {
    std::string ret;
    for(Range<T> r : ranges) {
        ret += r.to_string() + " ";
    }
    ret.pop_back();

    return ret;
}


template<typename T>
bool IntervalMap<T>::has_range(const Range<T>& r) const {
    unsigned int idx = binary_search(r.get_lower());
    return idx < ranges.size() && ranges[idx].encompass(r);
}
template<typename T>
bool IntervalMap<T>::has_val(const T& val) const {
    unsigned int idx = binary_search(val);
    return idx < ranges.size() && ranges[idx].includes(val);
}


template<typename T>
T IntervalMap<T>::lower_bound() const {
    if (ranges.empty()) {
        return T();
    }

    return ranges.front().get_lower();
}
template<typename T>
T IntervalMap<T>::upper_bound() const {
    if (ranges.empty()) {
        return T();
    }

    return ranges.back().get_upper();
}


template<typename T>
std::vector<Range<T>> IntervalMap<T>::get_ranges() const {
    return ranges;
}


template<typename T>
void IntervalMap<T>::insert_range(const Range<T>& r) {
    unsigned int idx = binary_search(r.get_lower());
    // If no intersecting range found, add the range plainly.
    if (idx >= ranges.size()) {
        ranges.push_back(r);
        return;
    }

    // If previous range borders this range, calculate from that instead.
    if (idx > 0 && ranges[idx - 1].get_upper() == r.get_lower()) {
        idx--;
    }

    Range<T> this_range = ranges[idx];
    // If no intersection or bordering found, add the range plainly.
    if (!this_range.intersects(r) && !this_range.bordering(r)) {
        // Increase index by one if this range needs to be placed above.
        idx += (this_range.get_lower() <= r.get_lower());

        ranges.insert(std::begin(ranges) + idx, r);
    } else {
        // If intersecting range found, union it to the smallest of such ranges.
        ranges[idx] = this_range.union_range(r);
    }

    // Loop through all proceeding ranges and find the first one that does not intersect the range.
    unsigned int next = idx + 1;
    while(next < ranges.size()) {
        if (ranges[idx].self_union(ranges[next])) {
            next++;
            continue;
        }
        break;
    }

    // Deletes all proceeding ranges before the first one that doesn't intersect.
    ranges.erase(std::begin(ranges) + idx + 1, std::begin(ranges) + next);
}


template<typename T>
void IntervalMap<T>::remove_range(const Range<T>& r)  {
    unsigned int idx = binary_search(r.get_lower());
    // If no intersecting range found, don't erase anything.
    if (idx >= ranges.size()) {
        return;
    }

    Range<T> this_range = ranges[idx];
    // If no intersection, don't erase anything.
    if (!this_range.intersects(r)) {
        return;
    }

    // If only intersecting in one range, split range into two.
    if (this_range.separate_subtracts(r)) {
        ranges[idx] = this_range.subtract_range_min(r);
        ranges.insert(std::begin(ranges) + idx + 1, this_range.subtract_range_max(r));
        return;
    }

    // Partially erases first range.
    ranges[idx] = this_range.subtract_range_min(r);
    
    // Goes down list and erases all elements in ranges.
    unsigned int next = idx + 1;
    while(next < ranges.size()) {
        this_range = ranges[next];

        // Stops if no more intersection.
        if (!this_range.intersects(r)) {
            break;
        }
        next++;
    }

    // Partially erases last range.
    ranges[next - 1] = this_range.subtract_range_min(r);

    // If last affected range still has elements, go back one.
    if (ranges[next - 1].size() > 0) {
        next -= 1;
    }
    
    // Deletes all empty ranges from list.
    ranges.erase(std::begin(ranges) + idx, std::begin(ranges) + next);
}



template class IntervalMap<char>;
template class IntervalMap<signed char>;
template class IntervalMap<unsigned char>;
template class IntervalMap<wchar_t>;

template class IntervalMap<short>;
template class IntervalMap<int>;
template class IntervalMap<long>;
template class IntervalMap<long long>;

template class IntervalMap<unsigned short>;
template class IntervalMap<unsigned int>;
template class IntervalMap<unsigned long>;
template class IntervalMap<unsigned long long>;

template class IntervalMap<float>;
template class IntervalMap<double>;
template class IntervalMap<long double>;

#if defined(__cpp_char8_t)
template class IntervalMap<char8_t>;
#endif
#if defined(__cpp_char16_t)
template class IntervalMap<char16_t>;
#endif
#if defined(__cpp_char32_t)
template class IntervalMap<char32_t>;
#endif