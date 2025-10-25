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
    int z;
};

inline long long sq_dist(point& a, point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    return dx*dx + dy*dy + dz*dz;
}

int main() {
    auto start_time = std::chrono::steady_clock::now();
    auto timeout = std::chrono::milliseconds(1000);
    
    int n;
    std::cin >> n;    

    std::vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y >> points[i].z;
    }
    
    std::vector<int> indecies(n);
    for (int i = 0; i < n; ++i) {
        indecies[i] = i;
    }

    std::sort(indecies.begin(), indecies.end(), [&](const int& i, const int& j) { return points[i].y < points[j].y; });

    std::vector<point> points_cp(n);
    for (int i = 0; i < n; ++i) {
        points_cp[i] = points[indecies[i]];
    }

    long long res = LLONG_MAX;
    int i1, i2;

    for (int d = 1; d < n; ++d) {
        for (int i = 0; i + d < n; ++i) {
            long long cur = sq_dist(points_cp[i], points_cp[i + d]);
            if (cur < res) {
                res = cur;
                i1 = i;
                i2 = i + d;
            }
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time) >= timeout) {
            break;
        }
    }

    std::cout << std::fixed << std::setprecision(7) << std::sqrt((long double)res) << std::endl;
    std::cout << indecies[i1]+1 << " " << indecies[i2]+1 << std::endl;
}