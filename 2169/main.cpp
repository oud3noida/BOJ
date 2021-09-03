#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int LEFT = 0,
              DOWN = 1,
              RIGHT = 2,
              UNDEFINED = numeric_limits<int>::min();
constexpr int DX[3] = {-1, 0, 1},
              DY[3] = {0, 1, 0};
int x_max, y_max;
vector<vector<int>> board;
vector<vector<vector<int>>> cache;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int max_value(int x, int y, int prev_dir) {
    if (!in_range(x, y)) return UNDEFINED;
    
    if (x == x_max-1 && y == y_max-1) return board[y][x];
    
    int &ret = cache[x][y][prev_dir];
    if (ret != UNDEFINED) return ret;
    
    for (int dir = 0; dir < 3; dir++) {
        if ((prev_dir ^ dir) == (LEFT ^ RIGHT)) {
            // (LEFT, RIGHT) or (RIGHT, LEFT)
            continue;
        }
        
        int x_next = x + DX[dir],
            y_next = y + DY[dir];
        
        int ret_next = max_value(x_next, y_next, dir);
        if (ret_next != UNDEFINED) {
            ret = max(ret, board[y][x] + ret_next);
        }
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<int>(x_max, 0));
    cache.assign(x_max, vector<vector<int>>(y_max, vector<int>(3, UNDEFINED)));
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            cin >> board[y][x];
        }
    }
    
    cout << max_value(0, 0, DOWN);
    
    return 0;
}
