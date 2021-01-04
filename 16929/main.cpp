#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DX[4] = {-1, 1, 0, 0},
          DY[4] = {0, 0, -1, 1};
int X, Y;
vector<string> board;
vector<vector<int>> depth;

bool in_range(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

bool find_cycle(int x, int y, int cur_depth) {
    depth[y][x] = cur_depth;
    for (int d=0; d<4; ++d) {
        int nx = x + DX[d],
            ny = y + DY[d];
        if (!in_range(nx, ny) || board[y][x] != board[ny][nx]) continue;
        if (depth[ny][nx] != -1) {
            if ((cur_depth - depth[ny][nx]) >= 3) return true;
            continue;
        }
        if (find_cycle(nx, ny, cur_depth+1)) return true;
    }
    return false;
}

bool find_any_cycle() {
    for (int y=0; y<Y; ++y) {
        for (int x=0; x<X; ++x) {
            if (depth[y][x] == -1 && find_cycle(x, y, 0))
                return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> Y >> X;
    board.assign(Y, "");
    depth.assign(Y, vector<int>(X, -1));

    for (int y=0; y<Y; ++y) cin >> board[y];

    cout << (find_any_cycle() ? "Yes" : "No");

    return 0;
}