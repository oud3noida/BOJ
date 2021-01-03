#include <iostream>
#include <vector>

using namespace std;

const int DX[8] = {-1, 0, 1, -1, 1, -1, 0, 1},
          DY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int X, Y, ans;
vector<vector<bool>> is_land, visited;

bool in_range(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

void traverse_island(int x, int y) {
    visited[y][x] = true;
    for (int d=0; d<8; ++d) {
        int nx = x + DX[d],
            ny = y + DY[d];
        if (!in_range(nx, ny)) continue;
        if (!visited[ny][nx] && is_land[ny][nx])
            traverse_island(nx, ny);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> X >> Y;
    while (!(X == 0 && Y == 0)) {
        is_land.assign(Y, vector<bool>(X, false));
        visited.assign(Y, vector<bool>(X, false));

        int tmp;
        for (int y=0; y<Y; ++y) {
            for (int x=0; x<X; ++x) {
                cin >> tmp;
                is_land[y][x] = (tmp == 1);
            }
        }

        ans = 0;
        for (int y=0; y<Y; ++y) {
            for (int x=0; x<X; ++x) {
                if (visited[y][x] || !is_land[y][x]) continue;
                traverse_island(x, y);
                ++ans;
            }
        }

        cout << ans << '\n';

        cin >> X >> Y;
    }

    return 0;
}