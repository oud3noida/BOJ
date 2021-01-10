#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DX[4] = {-1, 1, 0, 0},
        DY[4] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y;
    cin >> Y >> X;

    vector<vector<char>> board(Y, vector<char>(X, '.'));
    vector<vector<bool>> visited(Y, vector<bool>(X, false));

    queue<pair<pair<int, int>, int>> hedgehog_move;

    string row;
    for (int y=0; y<Y; ++y) {
        cin >> row;
        for (int x=0; x<X; ++x) {
            board[y][x] = row[x];
            switch (board[y][x]) {
                case 'S':
                    hedgehog_move.emplace(make_pair(x, y), 0);
                    visited[y][x] = true;
                    board[y][x] = '.';
                    break;
            }
        }
    }

    int ans = -1;
    int cur_t = -1;
    while (!hedgehog_move.empty()) {
        int x = hedgehog_move.front().first.first,
                y = hedgehog_move.front().first.second,
                t = hedgehog_move.front().second;
        hedgehog_move.pop();

        if (cur_t != t) {
            ++cur_t;

            for (int water_y=0; water_y < Y; ++water_y) {
                for (int water_x = 0; water_x < X; ++water_x) {
                    if (board[water_y][water_x] == '*')
                        board[water_y][water_x] = '~';
                }
            }

            for (int water_y=0; water_y < Y; ++water_y) {
                for (int water_x=0; water_x < X; ++water_x) {
                    if (board[water_y][water_x] != '~') continue;

                    for (int d=0; d<4; ++d) {
                        int water_nx = water_x + DX[d],
                                water_ny = water_y + DY[d];
                        if (!(0 <= water_nx && water_nx < X && 0 <= water_ny && water_ny < Y))
                            continue;
                        if (board[water_ny][water_nx] == '.') {
                            board[water_ny][water_nx] = '*';
                        }
                    }
                }
            }
        }

        for (int d=0; d<4; ++d) {
            int nx = x + DX[d],
                    ny = y + DY[d];
            if (!(0 <= nx && nx < X && 0 <= ny && ny < Y) || visited[ny][nx])
                continue;
            if (board[ny][nx] == 'D') {
                ans = t+1;
                break;
            } else if (board[ny][nx] == '.') {
                hedgehog_move.emplace(make_pair(nx, ny), t+1);
                visited[ny][nx] = true;
            }
        }

        if (ans != -1) break;
    }

    if (ans != -1) cout << ans;
    else cout << "KAKTUS";

    return 0;
}