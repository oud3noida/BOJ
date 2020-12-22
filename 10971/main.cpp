#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 10'000'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n, 0));
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cin >> cost[i][j];
    vector<int> permutation(n, 0);
    for (int i=0; i<n; ++i) permutation[i] = i;

    int minCost = INF;
    do {
        int curCost = 0;
        bool disconnected = false;
        for (int i=0; i<n; ++i) {
            curCost += cost[permutation[i]][permutation[(i+1)%n]];
            if (cost[permutation[i]][permutation[(i+1)%n]] == 0) {
                disconnected = true;
                break;
            }
        }
        if (disconnected) continue;
        minCost = min(minCost, curCost);
    } while (next_permutation(permutation.begin(), permutation.end()));

    cout << minCost;

    return 0;
}