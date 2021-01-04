#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> adj;
int visited_idx;
vector<int> visited, distance_to_cycle;

int find_cycle(int parent, int cur) {
    int ret = -1;
    visited[cur] = ++visited_idx;

    for (int child : adj[cur]) {
        if (child == parent) continue;
        if (visited[child] != -1) {
            if (visited[child] < visited[cur]) ret = child;
            continue;
        }

        int child_ret = find_cycle(cur, child);
        ret = child_ret != -1 ? child_ret : ret;
    }

    if (ret != -1) distance_to_cycle[cur] = 0;
    if (ret == cur) ret = -1;

    return ret;
}

void calc_distance(int parent, int cur) {
    distance_to_cycle[cur] = distance_to_cycle[parent] + 1;
    for (int child : adj[cur]) {
        if (child == parent) continue;
        calc_distance(cur, child);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    int a, b;
    adj.assign(N, vector<int>());
    for (int i=0; i<N; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    visited_idx = -1;
    visited.assign(N, -1);
    distance_to_cycle.assign(N, -1);

    find_cycle(-1, 0);

    for (int i=0; i<N; ++i) {
        if (distance_to_cycle[i] != 0) continue;
        for (int child : adj[i]) {
            if (distance_to_cycle[child] != 0) calc_distance(i, child);
        }
    }

    for (int d : distance_to_cycle) cout << d << ' ';

    return 0;
}