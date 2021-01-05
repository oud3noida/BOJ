#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 200;
const int DX[4] = {-1, 1, 0, 0},
        DY[4] = {0, 0, -1, 1};
int N, min_distance;
vector<vector<int>> grid;
vector<queue<pair<int, int>>> coast_list;

bool in_range(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void find_coast(int x, int y, int island) {
    grid[y][x] = 0 - island;

    bool is_coast = false;
    for (int d=0; d<4; ++d) {
        int nx = x + DX[d],
                ny = y + DY[d];
        if (!in_range(nx, ny) || grid[ny][nx] == 0 - island) continue;
        if (grid[ny][nx] == INF) is_coast = true;
        else find_coast(nx, ny, island);
    }
    if (is_coast) coast_list[island-1].emplace(x, y);
}

void find_bridge(int island) {
    vector<vector<int>> distance(grid);
    auto& q = coast_list[island-1];

    while (!q.empty()) {
        int x = q.front().first,
                y = q.front().second,
                next_distance = (distance[y][x] < 0) ? 1 : distance[y][x] + 1;
        q.pop();

        if (next_distance > min_distance) return;

        for (int d=0; d<4; ++d) {
            int nx = x + DX[d],
                    ny = y + DY[d];
            if (!in_range(nx, ny)) continue;
            if (distance[ny][nx] == INF) q.emplace(nx, ny);
            if (distance[ny][nx] < 0 && distance[ny][nx] != 0 - island) {
                min_distance = distance[y][x];
                return;
            }
            distance[ny][nx] = min(distance[ny][nx], next_distance);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    grid.assign(N, vector<int>(N, -1));
    min_distance = 200;

    int cell;
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            cin >> cell;
            grid[y][x] = (cell == 0) ? INF : 0;
        }
    }

    int num_island = 0;
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            if (grid[y][x] == 0) {
                coast_list.emplace_back();
                find_coast(x, y, ++num_island);
            }
        }
    }

    for (int i=1; i<=num_island; ++i) {
        find_bridge(i);
    }

    cout << min_distance;

    return 0;
}