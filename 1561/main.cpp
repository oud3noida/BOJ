#include <iostream>
#include <vector>

using namespace std;

constexpr long long MAX = 60'000'000'000;
int n, m;
vector<int> duration;

long long num_passengers(long long t) {
    if (t == 0) return 0;
    
    long long ret = m;
    for (auto d : duration) {
        ret += (t-1) / d;
    }
    return ret;
}

int solve() {
    long long left = 1, right = MAX;
    
    while (left < right) {
        long long mid = (left + right) / 2;
        if (n <= num_passengers(mid)) right = mid;
        else left = mid + 1;
    }
    
    vector<int> candidates;
    for (int i = 0; i < m; i++) {
        if ((left-1) % duration[i] == 0) {
            candidates.push_back(i + 1);
        }
    }
    
    long long index_at_time = n - num_passengers(left-1) - 1;
    return candidates[index_at_time % candidates.size()];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    duration.assign(m, 0);
    for (int i = 0; i < m; i++) {
        cin >> duration[i];
    }
    
    cout << solve();
    
    return 0;
}
