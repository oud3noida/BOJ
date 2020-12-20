#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string s;
    cin >> s;

    int s_len = s.length(), ans = 0;
    stack<int> cuts;
    for (int i=0; i<s_len; ++i) {
        if (i>0 && s[i-1] == '(' && s[i] == ')') {
            cuts.pop();
            if (!cuts.empty()) ++cuts.top();
        } else if (s[i] == '(') {
            cuts.push(0);
        } else {
            int tmp = cuts.top(); cuts.pop();
            ans += tmp + 1;
            if (!cuts.empty()) cuts.top() += tmp;
        }
    }

    cout << ans;

    return 0;
}