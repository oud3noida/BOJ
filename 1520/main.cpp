#include <iostream>
#include <vector>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int x_max, y_max;
vector<vector<int>> board, cache;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int ways(int x, int y) {
    if (x == x_max-1 && y == y_max-1) return 1;
    
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d],
            y_next = y + DY[d];
        
        if (!in_range(x_next, y_next)) continue;
        if (board[y][x] <= board[y_next][x_next]) continue;
        
        ret += ways(x_next, y_next);
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
    
    cout << ways(0, 0);
    
    return 0;
}
