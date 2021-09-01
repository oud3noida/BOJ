#include <iostream>
#include <vector>
#include <map>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int n;
vector<vector<int>> forest, greater_adj;
multimap<int, pair<int, int>> bamboos;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    forest.assign(n, vector<int>(n, 0));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> forest[y][x];
            bamboos.emplace(forest[y][x], make_pair(x, y));
        }
    }
    
    greater_adj.assign(n, vector<int>(n, -1));
    int ans = 0;
    for (auto bamboo = bamboos.rbegin(); bamboo != bamboos.rend(); ++bamboo) {
        auto [value, pos] = *bamboo;
        auto [x, y] = pos;
        
        greater_adj[y][x] = 1;
        
        for (int d = 0; d < 4; ++d) {
            int x_adj = x + DX[d];
            int y_adj = y + DY[d];
            
            if (!in_range(x_adj, y_adj)) continue;
            if (forest[y_adj][x_adj] <= forest[y][x]) continue;
            
            greater_adj[y][x] = max(greater_adj[y][x], greater_adj[y_adj][x_adj] + 1);
        }
        
        ans = max(ans, greater_adj[y][x]);
    }
    
    cout << ans;
    
    return 0;
}
