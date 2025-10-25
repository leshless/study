#pragma GCC optimize("O3")

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <climits>
#include <cmath>

struct point {
    int x;
    int y;
};

inline long long sq_dist(point& a, point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;

    return dx*dx + dy*dy;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto start_time = std::chrono::steady_clock::now();
    auto timeout = std::chrono::milliseconds(1000);

    std::vector<point> points;

    int x, y;
    while (std::cin >> x) {
        std::cin >> y;

        points.push_back({x, y});
    }
    
    int n = points.size();

    std::sort(points.begin(), points.end(), [](const point& a, const point& b) { return a.x < b.x; });

    long long res = LLONG_MAX;

    for (int d = 1; d < n; ++d) {
        for (int i = 0; i + d < n; ++i) {
            res = std::min(res, sq_dist(points[i], points[i + d]));

            if (i % 100 != 0) {
                continue;
            }

            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time) >= timeout) {
                goto end;
            }
        }
    }

    end:

    long double real_res = std::floor(std::sqrt((long double)res));
    std::cout << std::fixed << std::setprecision(0) << real_res << std::endl;
}