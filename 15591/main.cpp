#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

constexpr int INF = numeric_limits<int>::max();
int n, num_queries;
vector<vector<int>> adj, relevance, children;
vector<int> parent;
vector<bool> visited;

void dfs(int cur) {
    for (int child : adj[cur]) {
        if (!visited[child]) {
            visited[child] = true;
            children[cur].push_back(child);
            parent[child] = cur;
            dfs(child);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_queries;
    
    adj.assign(n, vector<int>());
    relevance.assign(n, vector<int>(n, INF));
    
    int a, b, r;
    for (int i = 0; i < n-1; i++) {
        cin >> a >> b >> r;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
        relevance[a-1][b-1] = r;
        relevance[b-1][a-1] = r;
    }
    
    parent.assign(n, -1);
    children.assign(n, vector<int>());
    visited.assign(n, false);
    visited[0] = true;
    dfs(0);
    
    for (int i = 0; i < n; i++) {
        queue<pair<int, int>> q;
        q.emplace(i, INF);
        while (!q.empty()) {
            auto [cur, cur_relevance] = q.front();
            q.pop();
            
            for (int child : children[cur]) {
                relevance[i][child] = min(cur_relevance, relevance[cur][child]);
                relevance[child][i] = relevance[i][child];
                q.emplace(child, relevance[i][child]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (relevance[i][j] != INF) continue;
            int common_parent = parent[i];
            while (relevance[common_parent][j] == INF) {
                common_parent = parent[common_parent];
            }
            relevance[i][j] = min(relevance[common_parent][i], relevance[common_parent][j]);
            relevance[j][i] = relevance[i][j];
        }
    }
    
    int k, x;
    for (int query = 0; query < num_queries; query++) {
        cin >> k >> x;
        
        int ans = 0;
        for (int rel : relevance[x-1]) {
            if (rel >= k) ++ans;
        }
        
        cout << ans-1 << '\n';
    }
    
    return 0;
}
