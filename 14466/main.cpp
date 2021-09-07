#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int n, num_cows, num_roads;
vector<vector<vector<vector<bool>>>> connected;
vector<vector<bool>> visited;
vector<vector<bool>> is_cow;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int connected_cows(int x, int y) {
    if (visited[y][x]) return 0;
    visited[y][x] = true;
    
    int ret = is_cow[y][x] ? 1 : 0;
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d];
        int y_next = y + DY[d];
        
        if (!in_range(x_next, y_next)) continue;
        if (!connected[y][x][y_next][x_next]) continue;
        ret += connected_cows(x_next, y_next);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_cows >> num_roads;
    
    connected.assign(n, vector<vector<vector<bool>>>(n,
                     vector<vector<bool>>(n, vector<bool>(n, true))));
    int x, y, a, b;
    for (int i = 0; i < num_roads; i++) {
        cin >> x >> y >> a >> b;
        connected[y-1][x-1][b-1][a-1] = false;
        connected[b-1][a-1][y-1][x-1] = false;
    }
    
    is_cow.assign(n, vector<bool>(n, false));
    for (int i = 0; i < num_cows; i++) {
        cin >> x >> y;
        is_cow[y-1][x-1] = true;
    }
    
    visited.assign(n, vector<bool>(n, false));
    vector<int> cow_pairs;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (!visited[y][x]) {
                cow_pairs.push_back(connected_cows(x, y));
            }
        }
    }
    
    int ans = 0;
    for (auto i = cow_pairs.begin(); i != cow_pairs.end(); i++) {
        for (auto j = next(i); j != cow_pairs.end(); j++) {
            ans += (*i) * (*j);
        }
    }
    
    cout << ans;
    
    return 0;
}
