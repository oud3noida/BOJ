#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> adj;
vector<bool> visited;

int find_five_friends(int cur, int depth) {
    if (depth == 5) return 1;

    visited[cur] = true;
    int ret = 0;

    for (int neighbor : adj[cur]) {
        if (visited[neighbor]) continue;
        ret = max(ret, find_five_friends(neighbor, depth+1));
        if (ret == 1) break;
    }

    visited[cur] = false;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    adj.assign(N, vector<int>());

    int a, b;
    for (int i=0; i<M; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;
    visited.assign(N, false);
    for (int i=0; i<N; ++i) {
        ans = max(ans, find_five_friends(i, 1));
    }

    cout << ans;

    return 0;
}