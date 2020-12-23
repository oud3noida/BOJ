#include <iostream>
#include <vector>

using namespace std;

struct appointment {
    int time, pay;
    appointment(int t, int p) : time(t), pay(p) {}
};

int n;
vector<appointment> appointments;
vector<int> cache;

int max_profit(int cur) {
    if (cur >= n) return 0;
    int& ret = cache[cur];
    if (ret != -1) return ret;

    int cur_time = appointments[cur].time, cur_pay = appointments[cur].pay;
    if (cur + cur_time <= n) ret = max(ret, cur_pay + max_profit(cur + cur_time));
    ret = max(ret, max_profit(cur + 1));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    int t, p;
    for (int i=0; i<n; ++i) {
        cin >> t >> p;
        appointments.emplace_back(t, p);
    }
    cache.assign(n, -1);

    cout << max_profit(0);

    return 0;
}