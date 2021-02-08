#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1'000'000'007;
vector<vector<int>> combination_cache;

int combination(int n, int k) {
    if (k == 0 || k == n) return 1;
    
    int &ret = combination_cache[n][k];
    if (ret == -1)
        ret = combination(n-1, k-1) + combination(n-1, k);
    return ret % MOD;
}

int main() {
    int n;
    cin >> n;
    
    combination_cache.assign(n+1, vector<int>(n+1, -1));
    
    int ans = 0;
    for (int k = 2-(n%3); k <= n-1; k += 3) {
        ans += combination(n-1, k);
        ans %= MOD;
    }
    cout << ans;

    return 0;
}
