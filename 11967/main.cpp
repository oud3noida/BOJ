#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int n, num_switches;
vector<vector<vector<pair<int, int>>>> switches;
vector<vector<int>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool adj_accessible(int x, int y) {
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d];
        int y_next = y + DY[d];
        if (!in_range(x_next, y_next)) continue;
        if (visited[y_next][x_next] == 1) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_switches;
    
    switches.assign(n, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>()));
    visited.assign(n, vector<int>(n, -1));
    int x, y, a, b;
    for (int i = 0; i < num_switches; i++) {
        cin >> x >> y >> a >> b;
        switches[y-1][x-1].emplace_back(a-1, b-1);
    }
    
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    visited[0][0] = 1;
    
    int ans = 1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int x_next = x + DX[d];
            int y_next = y + DY[d];
            if (!in_range(x_next, y_next)) continue;
            if (visited[y_next][x_next] == 0) {
                visited[y_next][x_next] = 1;
                q.emplace(x_next, y_next);
            }
        }
        
        for (auto [a, b] : switches[y][x]) {
            if (visited[b][a] == 1) continue;
            if (visited[b][a] == -1) ++ans;
            
            if (adj_accessible(a, b)) {
                visited[b][a] = 1;
                q.emplace(a, b);
            } else {
                visited[b][a] = 0;
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
