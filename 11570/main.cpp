#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int INF = numeric_limits<int>::max();
int n;
vector<int> tunes;
vector<vector<int>> last_sung;

int solve(int a, int b) {
    if (a == 1 && b == 0) return 0;
    if (a == 0 && b == 1) return 0;
    
    int &ret = last_sung[a][b];
    if (ret != INF) return ret;
    
    if (a-1 == b) {
        for (int i = 0; i < b; i++) {
            if (i == 0) ret = min(ret, solve(i, b));
            else ret = min(ret, solve(i, b) + abs(tunes[i] - tunes[a]));
        }
    } else if (b-1 == a) {
        for (int i = 0; i < a; i++) {
            if (i == 0) ret = min(ret, solve(a, i));
            else ret = min(ret, solve(a, i) + abs(tunes[i] - tunes[b]));
        }
    } else if (a > b) {
        if (a-1 == 0) ret = solve(a-1, b);
        else ret = solve(a-1, b) + abs(tunes[a-1] - tunes[a]);
    } else {
        if (b-1 == 0) ret = solve(a, b-1);
        else ret = solve(a, b-1) + abs(tunes[b-1] - tunes[b]);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    tunes.assign(n+1, 0);
    last_sung.assign(n+1, vector<int>(n+1, INF));
    for (int i = 1; i <= n; i++) {
        cin >> tunes[i];
    }
    
    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, solve(i, n));
        ans = min(ans, solve(n, i));
    }
    
    cout << ans;
    
    return 0;
}
