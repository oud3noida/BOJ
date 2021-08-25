#include <iostream>
#include <vector>

using namespace std;

int x_max, y_max;
vector<vector<int>> board, max_square;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

int find_max_square(int x, int y) {
    if (!in_range(x, y) || (board[y][x] != 0)) return 0;
    
    int &ret = max_square[y][x];
    if (ret != -1) return ret;
    
    int adj = find_max_square(x+1, y);
    adj = min(adj, find_max_square(x+1, y+1));
    adj = min(adj, find_max_square(x, y+1));
    
    ret = adj + 1;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<int>(x_max, 0));
    max_square.assign(y_max, vector<int>(x_max, -1));
    for (int y=0; y<y_max; ++y) {
        for (int x=0; x<x_max; ++x) {
            cin >> board[y][x];
        }
    }
    
    int ans = 0;
    for (int y=0; y<y_max; ++y) {
        for (int x=0; x<x_max; ++x) {
            ans = max(ans, find_max_square(x, y));
        }
    }
    
    cout << ans;
    
    return 0;
}
