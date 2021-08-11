#include <iostream>
#include <vector>

using namespace std;

constexpr char F = '.', T = '#';
int x_max, y_max;
vector<vector<bool>> board, target;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

char dir(int x_prev, int y_prev, int x, int y) {
    if (x - x_prev == 1) return 'R';
    if (x - x_prev == -1) return 'L';
    if (y - y_prev == 1) return 'D';
    if (y - y_prev == -1) return 'U';
    return '?';
}

void step_tile(int x_prev, int y_prev, int x, int y) {
    if (y == y_max) {
        cout << dir(x_prev, y_prev, x, y);
        if (board[y_prev][x_prev] != target[y_prev][x_prev]) {
            cout << 'U';
        }
        return;
    }
    
    if (x == x_max) return step_tile(x_prev, y_prev, x-1, y+1);
    if (x == -1) return step_tile(x_prev, y_prev, x+1, y+1);
    
    cout << dir(x_prev, y_prev, x, y);
    board[y][x] = !board[y][x];
    if (in_range(x_prev, y_prev) && board[y_prev][x_prev] != target[y_prev][x_prev]) {
        cout << dir(x, y, x_prev, y_prev);
        board[y_prev][x_prev] = !board[y_prev][x_prev];
        cout << dir(x_prev, y_prev, x, y);
        board[y][x] = !board[y][x];
    }
    step_tile(x, y, x + (y%2 == 0 ? 1 : -1), y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<bool>(x_max, false));
    target.assign(y_max, vector<bool>(x_max, false));
    char cell;
    for (int y = 0; y < y_max; ++y) {
        for (int x = 0; x < x_max; ++x) {
            cin >> cell;
            target[y][x] = (cell == T);
        }
    }
    
    step_tile(-1, 0, 0, 0);
    
    return 0;
}
