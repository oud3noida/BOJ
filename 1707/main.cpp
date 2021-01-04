#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T, num_vertex, num_edge;
vector<vector<int>> adj;
vector<int> vertex_color;

bool check_bipartite(int root, int root_color) {
    queue<pair<int, int>> q;
    q.emplace(root, root_color);
    vertex_color[root] = root_color;

    while (!q.empty()) {
        int cur = q.front().first,
            cur_color = q.front().second;
        q.pop();

        for (int neighbor : adj[cur]) {
            if (vertex_color[neighbor] != -1) {
                if (vertex_color[neighbor] == cur_color) return false;
                continue;
            }
            q.emplace(neighbor, (cur_color+1)%2);
            vertex_color[neighbor] = (cur_color+1)%2;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    for (int t=0; t<T; ++t) {
        cin >> num_vertex >> num_edge;
        adj.assign(num_vertex, vector<int>());
        vertex_color.assign(num_vertex, -1);

        int a, b;
        for (int e=0; e<num_edge; ++e) {
            cin >> a >> b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        bool is_bipartite = true;
        for (int v=0; v<num_vertex; ++v) {
            if (vertex_color[v] == -1 && !check_bipartite(v, 0)) {
                is_bipartite = false;
                break;
            }
        }

        cout << (is_bipartite ? "YES\n" : "NO\n");
    }

    return 0;
}