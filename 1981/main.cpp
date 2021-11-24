#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX = 200;
constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int n;
vector<vector<int>> board;
vector<vector<bool>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool is_possible(int x, int y, pair<int, int> bound) {
    if (x == n-1 && y == n-1) return true;
    
    visited[y][x] = true;
    auto [min_bound, max_bound] = bound;
    
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d],
            y_next = y + DY[d];
        
        if (!in_range(x_next, y_next) ||
            visited[y_next][x_next] ||
            min_bound > board[y_next][x_next] ||
            max_bound < board[y_next][x_next]) {
            continue;
        }
        
        if (is_possible(x_next, y_next, bound)) return true;
    }
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    board.assign(n, vector<int>(n, 0));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> board[y][x];
        }
    }
    
    int left = abs(board[0][0] - board[n-1][n-1]),
        right = MAX;
    
    while (left < right) {
        int mid = (left + right) / 2;
        bool check = false;
        int from = max(max(board[0][0], board[n-1][n-1]) - mid, 0),
            to = min(min(board[0][0], board[n-1][n-1]), MAX - mid);
        
        for (int i = from; i <= to; i++) {
            visited.assign(n, vector<bool>(n, false));
            if (is_possible(0, 0, make_pair(i, i + mid))) {
                check = true;
                break;
            }
        }
        
        if (check) right = mid;
        else left = mid + 1;
    }
    
    cout << left;
    
    return 0;
}
