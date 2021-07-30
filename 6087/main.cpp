#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int DX[4] = {0, 0, -1, 1},
              DY[4] = {-1, 1, 0, 0};
constexpr char BLANK = '.',
               WALL = '*',
               LASER = 'C';

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

int x_max, y_max;
vector<vector<char>> board;
vector<vector<bool>> visited;
queue<pair<Position*, int>> q;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> x_max >> y_max;
    
    bool laser_found = false;
    visited.assign(y_max, vector<bool>(x_max, false));
    board.assign(y_max, vector<char>(x_max, BLANK));
    for (int y=0; y<y_max; ++y) {
        for (int x=0; x<x_max; ++x) {
            cin >> board[y][x];
            
            if (board[y][x] == LASER && !laser_found) {
                laser_found = true;
                q.emplace(new Position(x, y), 0);
                visited[y][x] = true;
            }
        }
    }
    
    while (!q.empty()) {
        int x = q.front().first->x,
            y = q.front().first->y,
            mirror = q.front().second;
        q.pop();
                
        for (int dir=0; dir<4; ++dir) {
            int x_next = x + DX[dir],
                y_next = y + DY[dir];
            
            while (in_range(x_next, y_next) && board[y_next][x_next] != WALL) {
                if (!visited[y_next][x_next]) {
                    if (board[y_next][x_next] == LASER) {
                        cout << mirror;
                        return 0;
                    }
                    
                    q.emplace(new Position(x_next, y_next), mirror + 1);
                    visited[y_next][x_next] = true;
                }
                
                x_next += DX[dir];
                y_next += DY[dir];
            }
        }
    }
    
    return 0;
}
