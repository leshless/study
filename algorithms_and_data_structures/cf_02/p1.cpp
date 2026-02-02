#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>

struct Interval {
    int left;
    int right;

    size_t length() {
        return std::abs(this->right - this->left) + 1;
    }

    Interval overlap(const Interval& other){
        int left = std::max(this->left, other.left);
        int right = std::min(this->right, other.right);

        return Interval{left, right};
    }
};

void merge_sort(std::vector<Interval>& intervals, int l, int r){
    if (r - l <= 1) {
        return;
    }
    
    int m = l + (r - l) / 2;
    merge_sort(intervals, l, m);
    merge_sort(intervals, m, r);

    int i = l;
    int j = m;
    std::vector<Interval> sorted_intervals;
    while ((i != m) && (j != r)) {
        if (intervals[i].left < intervals[j].left) {
            sorted_intervals.push_back(intervals[i]);
            i++;
        } else {
            sorted_intervals.push_back(intervals[j]);
            j++;
        }
    }
    while (i != m) {
        sorted_intervals.push_back(intervals[i]);
        i++;
    }
    while (j != r) {
        sorted_intervals.push_back(intervals[j]);
        j++;
    }

    for (int i = 0; i < r - l; i++) {
        intervals[l + i] = sorted_intervals[i];
    }

    return;
}

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<Interval> intervals;
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;

        intervals.push_back(Interval{l, r});
    }

    // std::cout << std::endl;

    // for (auto interval : intervals) {
    //     std::cout << interval.left << " " << interval.right << std::endl;
    // }
    
    // std::cout << std::endl;

    merge_sort(intervals, 0, n);

    Interval cur = intervals[0];
    Interval res;
    bool found = false;

    for (int i = 1; i < n; i++) {
        Interval overlap = intervals[i].overlap(cur);
        if ((overlap.left <= overlap.right) && (!found || overlap.length() > res.length())) {
            found = true;
            res = overlap;
        }

        if (intervals[i].right > cur.right) {
            cur = intervals[i];
        }
    }

    if (!found) {
        std::cout << 0 << std::endl;
    } else {
        std::cout << res.length() << std::endl;
        std::cout << res.left << " " << res.right << std::endl;
    }

    return 0;
}////