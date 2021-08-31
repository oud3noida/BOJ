#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> schedule;
vector<int> cache;

int max_pay(int day) {
    if (day >= n) return 0;
    
    int &ret = cache[day];
    if (ret != -1) return ret;
    
    auto [t, p] = schedule[day];
    if (day + t <= n) ret = p + max_pay(day + t);
    ret = max(ret, max_pay(day + 1));
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int t, p;
    for (int i = 0; i < n; i++) {
        cin >> t >> p;
        schedule.emplace_back(t, p);
    }
    
    cache.assign(n, -1);
    cout << max_pay(0);
    
    return 0;
}
