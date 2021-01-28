#include <iostream>
#include <vector>

using namespace std;

const int INF = 9999;
int maze_size;
vector<int> maze, cache;

int min_num_jump(int cur) {
    if (cur >= maze_size - 1) return 0;

    int &ret = cache[cur];
    if (ret != -1) return ret;

    ret = INF;
    for (int i = 1; i <= maze[cur]; ++i) {
        ret = min(ret, min_num_jump(cur + i) + 1);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> maze_size;

    maze.assign(maze_size, 0);
    for (int i = 0; i < maze_size; ++i)
        cin >> maze[i];

    cache.assign(maze_size, -1);
    int ans = min_num_jump(0);
    cout << (ans != INF ? ans : -1);

    return 0;
}