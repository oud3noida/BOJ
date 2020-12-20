#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100'000, MOD = 1'000'000'009;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    vector<vector<int>> dp(MAX+1, vector<int>(4, 0));
    dp[1][1] = 1;
    dp[2][2] = 1;
    dp[3][1] = 1; dp[3][2] = 1; dp[3][3] = 1;

    for (int i=4; i<=MAX; ++i) {
        dp[i][1] = (dp[i-1][2] + dp[i-1][3]) % MOD;
        dp[i][2] = (dp[i-2][1] + dp[i-2][3]) % MOD;
        dp[i][3] = (dp[i-3][1] + dp[i-3][2]) % MOD;
    }

    int T, n;
    cin >> T;
    for (int i=0; i<T; ++i) {
        cin >> n;
        cout << ((dp[n][1] + dp[n][2]) % MOD + dp[n][3]) % MOD << "\n";
    }

    return 0;
}