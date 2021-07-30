#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

constexpr int MAX = 8;
constexpr int DX[9] = {-1, -1, -1, 0, 1, 1, 1, 0, 0},
              DY[9] = {-1, 0, 1, 1, 1, 0, -1, -1, 0};
constexpr char BLANK = '.',
               WALL = '#';

vector<string> board;
queue<pair<Position, int>> q;

bool in_range(int x, int y) {
    return 0 <= x && x < MAX && 0 <= y && y < MAX;
}

bool is_wall(int x, int y, int cur) {
    if (!in_range(x, y-cur)) return false;
    return board[y-cur][x] == WALL;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    board.assign(MAX, string());
    for (int y=0; y<MAX; ++y) {
        cin >> board[y];
    }
    
    q.emplace(Position(0, MAX-1), 0);
    
    while (!q.empty()) {
        Position pos = q.front().first;
        int cur = q.front().second;
        q.pop();
        
        if (cur >= MAX) {
            cout << 1;
            return 0;
        }
        
        for (int dir=0; dir<9; ++dir) {
            int x_next = pos.x + DX[dir],
                y_next = pos.y + DY[dir];
            
            if (in_range(x_next, y_next) && !is_wall(x_next, y_next, cur)) {
                if (x_next == MAX-1 && y_next == 0) {
                    cout << 1;
                    return 0;
                } else if (!is_wall(x_next, y_next, cur + 1)) {
                    q.emplace(Position(x_next, y_next), cur+1);
                }
            }
        }
    }
    
    cout << 0;
    
    return 0;
}
