#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <climits>

const double EPS = 1e-7;
const double MAX = 1e7;

int main() {
    int L, n;
    std::cin >> L >> n;

    std::vector<std::pair<double, double>> intervals;
    for (int i = 0; i < n; i++) {
        double t, v;
        std::cin >> t >> v;

        intervals.push_back({t, v});
    }

    double l = EPS;
    double r = MAX;

    while (r - l > EPS) {
        double m = l + (r - l) / 2;

        bool failed = false;
        for (int i = 0; i < n; i++) {
            double t = m;
            double s = 0;
            int j = i;

            while (j >= 0 && t > 0) {
                s += std::min(t, intervals[j].first) * intervals[j].second;
                t -= std::min(t, intervals[j].first);
                j--;
            }

            if (t == 0 && s < L) {
                failed = true;
                break;
            }
        }

        if (failed) {
            l = m;
            continue;
        }

        failed = false;
        for (int i = 0; i < n; i++) {
            double t = m;
            double s = 0;
            int j = i;

            while (j < n && t > 0) {
                s += std::min(t, intervals[j].first) * intervals[j].second;
                t -= std::min(t, intervals[j].first);
                j++;
            }

            if (t == 0 && s < L) {
                failed = true;
                break;
            }
        }

        if (failed) {
            l = m;
        } else {
            r = m;
        }
    }

    std::cout << std::fixed << std::setprecision(5) << l << std::endl;
}