#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1'000'000, MOD = 1'000'000'009;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    vector<int> dp(MAX+1, 0);
    dp[1] = 1; dp[2] = 2; dp[3] = 4;

    for (int i=4; i<=MAX; ++i) {
        dp[i] = (((dp[i-1] + dp[i-2]) % MOD) + dp[i-3]) % MOD;
    }

    int T, n;
    cin >> T;
    for (int i=0; i<T; ++i) {
        cin >> n;
        cout << dp[n] << "\n";
    }

    return 0;
}