#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int DX[6] = {-2, -2, 0, 0, 2, 2},
              DY[6] = {-1, 1, -2, 2, -1, 1};

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

int n;
vector<vector<bool>> visited;
queue<pair<Position*, int>> q;
Position* destination;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    visited.assign(n, vector<bool>(n, false));
    
    int x, y;
    cin >> x >> y;
    q.emplace(new Position(x, y), 0);
    visited[y][x] = true;
    
    cin >> x >> y;
    destination = new Position(x, y);
    
    int ans = -1;
    while (!q.empty()) {
        x = q.front().first->x;
        y = q.front().first->y;
        int cur = q.front().second;
        q.pop();
        
        if (x == destination->x && y == destination->y) {
            ans = cur;
            break;
        }
        
        for (int dir=0; dir<6; ++dir) {
            int x_next = x + DX[dir],
                y_next = y + DY[dir];
            
            if (!in_range(x_next, y_next) || visited[y_next][x_next]) continue;
            
            q.emplace(new Position(x_next, y_next), cur+1);
            visited[y_next][x_next] = true;
        }
    }
    
    cout << ans;
    
    return 0;
}
