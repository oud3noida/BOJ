#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    cin >> n;

    vector<vector<int>> distance(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> distance[i][j];
        }
    }

    for (int m = 0; m < n; ++m) {
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                if (!distance[a][b] && distance[a][m] && distance[m][b]) distance[a][b] = 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << distance[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
