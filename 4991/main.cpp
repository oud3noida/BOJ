#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int x, y, cleared_dust, t;
    
    State(int x, int y, int cleared_dust, int t) :
        x(x), y(y), cleared_dust(cleared_dust), t(t) {}
};

constexpr int INF = 1'987'654'321;
constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
constexpr int WALL = -1, CLEAN = 0;
int x_max, y_max;
vector<vector<int>> board;
vector<vector<vector<bool>>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

bool is_dust(int x, int y) {
    return board[y][x] > 0;
}
    
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    while (true) {
        cin >> x_max >> y_max;
        if (x_max == 0 && y_max == 0) break;
        
        board.assign(y_max, vector<int>(x_max, CLEAN));
        visited.assign(y_max, vector<vector<bool>>(x_max, vector<bool>(1<<10, false)));
        
        char cell;
        int dust_index = 1;
        queue<State> q;
        for (int y = 0; y < y_max; y++) {
            for (int x = 0; x < x_max; x++) {
                cin >> cell;
                
                if (cell == 'o') {
                    q.emplace(x, y, 0, 0);
                    visited[y][x][0] = true;
                } else if (cell == '*') {
                    board[y][x] = dust_index;
                    dust_index <<= 1;
                } else if (cell == 'x') { 
                    board[y][x] = WALL;
                }
            }
        }
        
        int ans = INF;
        while (!q.empty()) {
            auto cur = q.front();
            int x = cur.x,
                y = cur.y,
                cleared_dust = cur.cleared_dust,
                t = cur.t;
            q.pop();
            
            if (cleared_dust == dust_index - 1) {
                ans = min(ans, t);
            }
            
            for (int d = 0; d < 4; d++) {
                int x_next = x + DX[d];
                int y_next = y + DY[d];
                
                if (!in_range(x_next, y_next) || board[y_next][x_next] == WALL) continue;
                
                if (is_dust(x_next, y_next)) {
                    int cur_dust = board[y_next][x_next];
                    if (visited[y_next][x_next][cleared_dust | cur_dust]) continue;
                    q.emplace(x_next, y_next, cleared_dust | cur_dust, t + 1);
                    visited[y_next][x_next][cleared_dust | cur_dust] = true;
                } else {
                    if (visited[y_next][x_next][cleared_dust]) continue;
                    q.emplace(x_next, y_next, cleared_dust, t + 1);
                    visited[y_next][x_next][cleared_dust] = true;
                }
            }
        }
        
        if (ans == INF) cout << "-1\n";
        else cout << ans << '\n';
    }
    
    return 0;
}
