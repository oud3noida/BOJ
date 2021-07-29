#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 1000;

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

constexpr int DX[4] = {0, 0, -1, 1},
              DY[4] = {-1, 1, 0, 0};
constexpr char DIR_CHAR[4] = {'U', 'D', 'L', 'R'};

int x_max, y_max;
vector<vector<int>> board;
int x_exclude, y_exclude;
bool exclude;

vector<Direction> route;
vector<vector<bool>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

bool go_right;

bool find_route_with_dir(int x, int y, int cur, Direction dir);

bool find_route(int x, int y, int cur) {
    if (!in_range(x, y)) return false;
    if (visited[y][x]) return false;
    if (exclude && x == x_exclude && y == y_exclude) return false;
    
    if (x == x_max - 1 && y == y_max - 1) {
        return cur == (x_max * y_max - (exclude ? 2 : 1));
    }
    
    visited[y][x] = true;
    
    if (x == 0) go_right = true;
    if (x == x_max - 1) go_right = false;
    
    bool zigzag = (y_max%2 == 0 && go_right && y/2 == (y_max - 1)/2) ||
                  (exclude && y/2 == y_exclude/2);
    if (zigzag) {
        if (y%2 == 0) {
            if (find_route_with_dir(x, y, cur, DOWN)) return true;
        } else {
            if (find_route_with_dir(x, y, cur, UP)) return true;
        }
    }
    
    return find_route_with_dir(x, y, cur, go_right ? RIGHT : LEFT) ||
           find_route_with_dir(x, y, cur, DOWN);
}

bool find_route_with_dir(int x, int y, int cur, Direction dir) {
    int x_next = x + DX[(int) dir],
        y_next = y + DY[(int) dir];
    route[cur] = dir;
    
    return find_route(x_next, y_next, cur+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<int>(x_max, 0));
    x_exclude = 1;
    y_exclude = 0;
    for (int y=0; y<y_max; ++y) {
        for (int x=0; x<x_max; ++x) {
            cin >> board[y][x];
            if (board[y][x] < board[y_exclude][x_exclude] && (x+y)%2 == 1) {
                x_exclude = x;
                y_exclude = y;
            }
        }
    }
    
    exclude = x_max%2 == 0 && y_max%2 == 0;
    visited.assign(y_max, vector<bool>(x_max, false));
    route.assign(x_max*y_max - (exclude ? 2 : 1), NONE);
    find_route(0, 0, 0);
    
    for (auto dir : route) {
        cout << DIR_CHAR[(int) dir];
    }
    
    return 0;
}
