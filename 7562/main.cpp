#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int x, y, num_move;
    State(int x, int y, int num_move) :
    x(x), y(y), num_move(num_move) {}
};

const int DX[8] = {-2, -1, 1, 2, -2, -1, 1, 2},
          DY[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int N, x_from, y_from, x_to, y_to;
vector<vector<bool>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

int min_move() {
    queue<State> q;
    q.emplace(x_from, y_from, 0);
    visited[y_from][x_from] = true;

    while (!q.empty()) {
        int x_cur = q.front().x,
            y_cur = q.front().y,
            cur_move = q.front().num_move;
        q.pop();

        if (!in_range(x_cur, y_cur)) continue;
        if (x_cur == x_to && y_cur == y_to) return cur_move;

        for (int d=0; d<8; ++d) {
            int x_next = x_cur + DX[d],
                y_next = y_cur + DY[d];
            if (!in_range(x_next, y_next) || visited[y_next][x_next]) continue;
            visited[y_next][x_next] = true;
            q.emplace(x_next, y_next, cur_move+1);
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t=0; t<T; ++t) {
        cin >> N;
        cin >> x_from >> y_from >> x_to >> y_to;
        visited.assign(N, vector<bool>(N, false));

        cout << min_move() << '\n';
    }

    return 0;
}