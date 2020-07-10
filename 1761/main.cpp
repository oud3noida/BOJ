#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> intPair;

const int MAX = 40000;
int n, q;
int depth[MAX];
bool visited[MAX];
vector<intPair> adj[MAX]; // (vertex, distance)
intPair parent[MAX];      // (vertex, distance)

void makeTree(int cur, int d) {
    depth[cur] = d;
    visited[cur] = true;
    for (auto &next : adj[cur]) {
        int v = next.first, cost = next.second;
        if (visited[v]) continue;
        parent[v] = make_pair(cur, cost);
        makeTree(v, d+1);
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int LCA_distance(int a, int b) {
    int ret = 0;
    
    if (depth[a] < depth[b]) swap(a, b);
    while (depth[a] > depth[b]) {
        ret += parent[a].second;
        a = parent[a].first;
    }
    
    while (a != b) {
        ret += parent[a].second;
        a = parent[a].first;
        ret += parent[b].second;
        b = parent[b].first;
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    int a, b, c;
    for (int i=0; i<n-1; ++i) {
        cin >> a >> b >> c;
        adj[a-1].push_back(make_pair(b-1, c));
        adj[b-1].push_back(make_pair(a-1, c));
    }
    makeTree(0, 0);
    
    cin >> q;
    for (int i=0; i<q; ++i) {
        cin >> a >> b;
        cout << LCA_distance(a-1, b-1) << "\n";
    }
    
    return 0;
}
