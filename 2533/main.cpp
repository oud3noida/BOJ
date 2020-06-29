#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 1000000;
int n;
vector<int> adj[MAX], child[MAX];
int cache[MAX][2];

void makeTree(int root) {
    queue<int> q;
    bool visited[n];
    fill(visited, visited+n, false);
    
    q.push(root);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        visited[cur] = true;
        for (auto &c : adj[cur]) {
            if (visited[c]) continue;
            q.push(c);
            child[cur].push_back(c);
        }
    }
}

int earlyAdaptor(int cur, bool par) {
    if (child[cur].empty()) return (par ? 0 : 1);
    
    int &ret = cache[cur][par ? 1 : 0];
    if (ret != -1) return ret;
    
    int include = 1, exclude = 0;
    
    for (auto &c : child[cur]) {
        include += earlyAdaptor(c, true);
        if (par) exclude += earlyAdaptor(c, false);
    }
    
    // If the parent node is marked as an early adaptor,
    // it does not matter whether the current node is an early adaptor or not.
    if (par) return ret = min(include, exclude);
    // Otherwise, the current node must be an early adaptor.
    else return ret = include;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int a, b;
    for (int i=0; i<n-1; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    
    makeTree(0);
    
    fill_n(*cache, 2*MAX, -1);
    cout << earlyAdaptor(0, true);
    
    return 0;
}
