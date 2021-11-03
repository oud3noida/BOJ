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
        int a, b;
        cin >> a >> b;
        distance[a - 1][b - 1] = 1;
        distance[b - 1][a - 1] = 1;
    }

    for (int m = 0; m < n; ++m) {
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                distance[a][b] = min(distance[a][b], distance[a][m] + distance[m][b]);
            }
        }
    }

    int ans = -1, min_bacon_num = INF;
    for (int i = 0; i < n; ++i) {
        int cur_bacon_num = 0;
        for (int j = 0; j < n; ++j) {
            cur_bacon_num += distance[i][j];
        }
        if (min_bacon_num > cur_bacon_num) {
            min_bacon_num = cur_bacon_num;
            ans = i;
        }
    }

    cout << ans + 1;

    return 0;
}
