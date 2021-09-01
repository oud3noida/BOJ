#include <iostream>
#include <vector>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};

int y_max, x_max, ans;
vector<string> board;
vector<vector<bool>> visited;
vector<vector<int>> cache;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int traverse(int x, int y) {
    int &ret = cache[y][x];
    if (ret != -1) {
        return ret;
    }
    
    ret = 1;
    
    for (int d = 0; d < 4; d++) {
        int distance = (int) (board[y][x] - '0');
        int x_next = x + DX[d] * distance;
        int y_next = y + DY[d] * distance;
        
        if (!in_range(x_next, y_next)) continue;
        if (board[y_next][x_next] == 'H') continue;
        
        if (visited[y_next][x_next]) return -1;
        
        visited[y_next][x_next] = true;
        
        int ret_next = traverse(x_next, y_next);
        if (ret_next == -1) return -1;
        ret = max(ret, ret_next + 1);
        
        visited[y_next][x_next] = false;
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, string());
    visited.assign(y_max, vector<bool>(x_max, false));
    cache.assign(y_max, vector<int>(x_max, -1));
    for (int y = 0; y < y_max; y++) {
        cin >> board[y];
    }
    
    visited[0][0] = true;
    
    cout << traverse(0, 0);
    
    return 0;
}
