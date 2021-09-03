#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int DX[3] = {1, 0, 1},
              DY[3] = {0, 1, 1};
int x_max, y_max;
vector<vector<int>> board, cache;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int max_value(int x, int y) {
    if (!in_range(x, y)) return 0;
    
    if (x == x_max-1 && y == y_max-1) return board[y][x];
    
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    
    for (int dir = 0; dir < 3; dir++) {        
        int x_next = x + DX[dir],
            y_next = y + DY[dir];
        
        int ret_next = max_value(x_next, y_next);
        ret = max(ret, board[y][x] + ret_next);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<int>(x_max, 0));
    cache.assign(y_max, vector<int>(x_max, -1));
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            cin >> board[y][x];
        }
    }
    
    cout << max_value(0, 0);
    
    return 0;
}
