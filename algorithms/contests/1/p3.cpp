#include <iostream>
#include <stack>
#include <string>
#include <utility>

int main() {
    std::string s;
    std::getline(std::cin, s);

    int n = s.size();

    std::string res = "";
    std::stack<std::pair<int, std::string>> st;

    for (int i = 0; i < n; i++) {
        if (('0' <= s[i]) && (s[i] <= '9')) {
            st.push({s[i] - '0', ""});
            continue;
        }
        if (s[i] == '[') {
            continue;
        }
        if (s[i] == ']') {
            int num = st.top().first;
            std::string cur = st.top().second;
            st.pop();

            if (num == 0) {
                cur.clear();
            } else {
                num--;
                
                std::string old = cur;
                while (num--) {
                    cur += old;
                }
            }

            if (st.empty()) {
                res += cur;
            } else {
                st.top().second += cur;
            } 

            continue;
        }

        if (!st.empty()){
            st.top().second += s[i];
        } else {
            res += s[i];
        }        
    }

    std::cout << res << std::endl;


    return 0;
}