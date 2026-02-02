#include <iostream>
#include <vector>
#include <stack>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    
    std::stack<int> st;
    std::vector<int> res;
    int tar = 1;
    int i = 0;
    
    while (1) {
        int cur = 0;
        while (1) {
            st.push(nums[i]);
            i++;
            cur++;

            if ((i == n) || (st.top() == tar)) {
                break;
            }
        }
        
        res.push_back(cur);
        
        cur = 0;
        while (1) {
            if ((st.empty()) || (st.top() != tar)) {
                break;
            }
            
            st.pop();
            tar++;
            cur++;
        }
        
        res.push_back(cur);
        
        if (i == n) {
            break;
        }
    }
    
    if (!st.empty()) {
        std::cout << "0" << std::endl;
        return 0;
    }

    for (int i = 0; i < res.size(); i+=2) {
        std::cout << "1 " << res[i] << std::endl;
        std::cout << "2 " << res[i+1] << std::endl;
    }

    return 0;
}