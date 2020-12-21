#include <iostream>
#include <vector>

using namespace std;

int N;
vector<string> board;
vector<vector<bool>> visited;

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

int max_vertical() {
    int ret = 1;
    visited.assign(N, vector<bool>(N, false));
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            if (visited[y][x]) continue;
            visited[y][x] = true;
            int dx = 1;
            while (x + dx < N && board[y][x + dx] == board[y][x]) ++dx;
            ret = max(ret, dx);
        }
    }

    return ret;
}

int max_horizontal() {
    int ret = 1;
    visited.assign(N, vector<bool>(N, false));
    for (int x=0; x<N; ++x) {
        for (int y=0; y<N; ++y) {
            if (visited[y][x]) continue;
            visited[y][x] = true;
            int dy = 1;
            while (y + dy < N && board[y + dy][x] == board[y][x]) ++dy;
            ret = max(ret, dy);
        }
    }

    return ret;
}

int find_same_color(int x, int y, int dx, int dy) {
    int x0 = x, y0 = y, ret = -1;
    while (inRange(x, y) && board[y][x] == board[y0][x0]) {
        x += dx;
        y += dy;
        ++ret;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    string row;
    for (int i=0; i<N; ++i) {
        cin >> row;
        board.push_back(row);
    }

    int ans = max(max_vertical(), max_horizontal());
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            if (x+1 < N) {
                swap(board[y][x], board[y][x+1]);
                ans = max(ans, 1 + find_same_color(x, y, 0, -1) + find_same_color(x, y, 0, 1));
                ans = max(ans, 1 + find_same_color(x+1, y, 0, -1) + find_same_color(x+1, y, 0, 1));
                ans = max(ans, 1 + find_same_color(x, y, 1, 0) + find_same_color(x, y, -1, 0));
                swap(board[y][x], board[y][x+1]);
            }
            if (y+1 < N) {
                swap(board[y][x], board[y+1][x]);
                ans = max(ans, 1 + find_same_color(x, y, 1, 0) + find_same_color(x, y, -1, 0));
                ans = max(ans, 1 + find_same_color(x, y+1, 1, 0) + find_same_color(x, y+1, -1,0));
                ans = max(ans, 1 + find_same_color(x, y, 0, -1) + find_same_color(x, y, 0, 1));
                swap(board[y][x], board[y+1][x]);
            }
        }
    }

    cout << ans;

    return 0;
}