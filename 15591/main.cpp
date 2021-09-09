#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

constexpr int INF = numeric_limits<int>::max();
int n, num_queries;
vector<vector<int>> adj, relevance;

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
    
    int k, x;
    for (int query = 0; query < num_queries; query++) {
        cin >> k >> x;
        
        int ans = 0;
        
        vector<bool> visited(n, false);
        queue<int> q;
        visited[x-1] = true;
        q.push(x-1);
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            ++ans;
            
            for (int neighbor : adj[cur]) {
                if (visited[neighbor]) continue;
                if (relevance[cur][neighbor] < k) continue;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
        
        cout << ans - 1 << '\n';
    }
    
    return 0;
}
