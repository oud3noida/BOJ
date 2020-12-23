#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 99999;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> stat(n, vector<int>(n, 0));
    vector<int> permutation(n, 0);
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) cin >> stat[i][j];

    int min_diff_stat = INF;
    for (int p=1; p<n; ++p) {
        for (int i=n-p; i<n; ++i) permutation[i] = 1;
        do {
            int stat_start = 0, stat_link = 0;
            vector<int> team_start, team_link;
            for (int i = 0; i < n; ++i) {
                if (permutation[i] == 0) {
                    for (int j : team_start) stat_start += stat[i][j] + stat[j][i];
                    team_start.push_back(i);
                } else {
                    for (int j : team_link) stat_link += stat[i][j] + stat[j][i];
                    team_link.push_back(i);
                }
            }
            min_diff_stat = min(min_diff_stat, abs(stat_start - stat_link));
        } while (next_permutation(++permutation.begin(), permutation.end()));
    }

    cout << min_diff_stat;

    return 0;
}