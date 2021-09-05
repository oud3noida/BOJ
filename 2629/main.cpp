#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX = 15000,
              POSSIBLE_MAX = 40000;
int n, tests, target;
vector<int> weights;
vector<vector<bool>> visited;
vector<bool> is_possible;

void solve(int i, int cur) {
    if (i > n) return;
    
    if (visited[i][cur]) return;
    visited[i][cur] = true;
    is_possible[cur] = true;
    
    solve(i+1, cur);
    solve(i+1, cur + weights[i]);
    solve(i+1, abs(cur - weights[i]));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    weights.assign(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    visited.assign(n+1, vector<bool>(MAX+1, false));
    is_possible.assign(POSSIBLE_MAX+1, false);
    solve(0, 0);
    
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        cin >> target;
        cout << (is_possible[target] ? "Y " : "N ");
    }
    
    return 0;
}
