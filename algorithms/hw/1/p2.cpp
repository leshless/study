#include <iostream>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    std::set<std::vector<int>> rots;
    for (int i = 0; i < n; i++) {
        std::vector<int> rot;
        for (int j = 0; j < n; j++) {
            rot.push_back(nums[(i + j) % n]);
        }

        rots.insert(rot);
    }

    std::vector<int> dsts;
    for (auto rot : rots) {
        int dst = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != rot[i]) {
                dst++;
            }
        }

        dsts.push_back(dst);
    }

    int mx = 0;
    for (int i = 0; i < dsts.size(); i++) {
        mx = std::max(dsts[i], mx);
    }

    int res = 0;
    for (int i = 0; i < dsts.size(); i++) {
        if (dsts[i] == mx) {
            res++;
        }
    }

    std::cout << res << std::endl;

    return 0;
}