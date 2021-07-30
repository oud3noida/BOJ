#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

struct State {
    Position pos;
    int num_break, distance;
    
    State(Position pos, int num_break, int distance)
        : pos(pos), num_break(num_break), distance(distance) {}
};

constexpr int INF = 11;
constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
constexpr char BLANK = '0',
               WALL = '1';
int x_max, y_max, max_break;
vector<vector<char>> board;
vector<vector<int>> num_broken_walls;
queue<State> q;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max >> max_break;
    
    board.assign(y_max, vector<char>(x_max, BLANK));
    num_broken_walls.assign(y_max, vector<int>(x_max, INF));
    string row;
    for (int y=0; y<y_max; ++y) {
        cin >> row;
        for (int x=0; x<x_max; ++x) {
            board[y][x] = row[x];
        }
    }
    
    q.emplace(Position(0, 0), 0, 1);
    num_broken_walls[0][0] = 0;
    
    while (!q.empty()) {
        State &cur = q.front();
        int x = cur.pos.x,
            y = cur.pos.y,
            num_break = cur.num_break,
            distance = cur.distance;
        q.pop();
        
        if (x == x_max - 1 && y == y_max - 1) {
            cout << distance;
            return 0;
        }
        
        for (int dir=0; dir<4; ++dir) {
            int x_next = x + DX[dir],
                y_next = y + DY[dir];
            
            if (!in_range(x_next, y_next)) continue;
            
            if (board[y_next][x_next] != WALL || num_break < max_break) {
                int num_break_next = num_break + ((board[y_next][x_next] == WALL) ? 1 : 0);
                
                if (num_broken_walls[y_next][x_next] <= num_break_next) continue;
                
                q.emplace(Position(x_next, y_next), num_break_next, distance+1);
                num_broken_walls[y_next][x_next] = num_break_next;
            }
        }
    }
    
    cout << -1;
    
    return 0;
}
