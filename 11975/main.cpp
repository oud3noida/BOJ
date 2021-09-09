#include <iostream>
#include <vector>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int n, x, y, x_min, x_max, y_min, y_max;
vector<vector<bool>> board;
string s;

bool in_range(int x, int y) {
    return x_min <= x && x <= x_max && y_min <= y && y <= y_max;
}

void visit_all_connected(int x, int y) {
    board[x][y] = true;
    
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d];
        int y_next = y + DY[d];
        
        if (!in_range(x_next, y_next)) continue;
        if (board[x_next][y_next]) continue;
        
        visit_all_connected(x_next, y_next);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    board.assign(4*n + 1, vector<bool>(4*n + 1, false));
    x = 2*n;
    y = 2*n;
    board[x][y] = true;
    
    cin >> s;
    
    x_min = 2*n;
    x_max = 2*n;
    y_min = 2*n;
    y_max = 2*n;
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
            case 'N':
                board[x][y-1] = true;
                board[x][y-2] = true;
                y -= 2;
                y_min = min(y_min, y);
                break;
            case 'S':
                board[x][y+1] = true;
                board[x][y+2] = true;
                y += 2;
                y_max = max(y_max, y);
                break;
            case 'W':
                board[x-1][y] = true;
                board[x-2][y] = true;
                x -= 2;
                x_min = min(x_min, x);
                break;
            case 'E':
                board[x+1][y] = true;
                board[x+2][y] = true;
                x += 2;
                x_max = max(x_max, x);
                break;
        }
    }
    
    x_min = max(x_min - 1, 0);
    x_max = min(x_max + 1, 4*n);
    y_min = max(y_min - 1, 0);
    y_max = min(y_max + 1, 4*n);
        
    int ans = 0;
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            if (board[x][y]) continue;
            ++ans;
            visit_all_connected(x, y);
        }
    }
    
    cout << ans - 1;
    
    return 0;
}
