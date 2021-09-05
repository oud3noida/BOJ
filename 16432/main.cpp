#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX = 9;
int num_days;
vector<vector<bool>> cakes;
vector<vector<int>> cache;
vector<int> ans;

bool solve(int day, int cur_cake) {
    if (day == num_days - 1) {
        ans[day] = cur_cake;
        return true;
    }
    
    int &ret = cache[day][cur_cake];
    if (ret != -1) return ret;
    
    for (int next_cake = 0; next_cake < MAX; next_cake++) {
        if (cur_cake == next_cake) continue;
        if (!cakes[day + 1][next_cake]) continue;
        
        if (solve(day + 1, next_cake)) {
            ans[day] = cur_cake;
            ret = 1;
            return true;
        }
    }
    ret = 0;
    return false;
}

bool is_possible() {
    for (int i = 0; i < MAX; i++) {
        if (!cakes[0][i]) continue;
        if (solve(0, i) == 1) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_days;
    
    cakes.assign(num_days, vector<bool>(MAX, false));
    int num_cakes;
    for (int d = 0; d < num_days; d++) {
        cin >> num_cakes;
        
        int cake;
        for (int i = 0; i < num_cakes; i++) {
            cin >> cake;
            cakes[d][cake-1] = true;
        }
    }
    
    cache.assign(num_days, vector<int>(MAX, -1));
    ans.assign(num_days, -1);
    
    if (is_possible()) {
        for (int cake : ans) {
            cout << cake + 1 << '\n';
        }
    } else {
        cout << -1;
    }
    
    return 0;
}
