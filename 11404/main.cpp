#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 123'456'789;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, num_edges;

    cin >> n >> num_edges;

    vector<vector<int>> distance(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        distance[i][i] = 0;
    }

    for (int i = 0; i < num_edges; ++i) {
        int a, b, cost;
        cin >> a >> b >> cost;
        distance[a - 1][b - 1] = min(distance[a - 1][b - 1], cost);
    }

    for (int m = 0; m < n; ++m) {
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                distance[a][b] = min(distance[a][b], distance[a][m] + distance[m][b]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (distance[i][j] != INF ? distance[i][j] : 0) << ' ';
        }
        cout << '\n';
    }

    return 0;
}
