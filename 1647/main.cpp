#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int cost, a, b;
    
    edge(int c, int i, int j) : cost(c), a(i), b(j) {}
};

bool compEdge(edge const& a, edge const& b) {
    return a.cost < b.cost;
}

const int MAX = 100000;
int n, m, ans;
vector<edge> edges;

class unionFind {
    private:
    int numSet;
    int parent[MAX], rank[MAX];
    
    public:
    unionFind(int size) {
        numSet = size;
        for (int i=0; i<size; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    
    void merge(int a, int b) {
        int rootA = find(a), rootB = find(b);
        if (rank[rootA] == rank[rootB]) {
            parent[rootA] = rootB;
            rank[rootB]++;
        }
        else if (rank[rootA] < rank[rootB]) parent[rootA] = rootB;
        else parent[rootB] = rootA;
        numSet--;
    }
    
    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    
    int a, b, c;
    for (int i=0; i<m; i++) {
        cin >> a >> b >> c;
        edges.push_back(edge(c, a-1, b-1));
    }
    sort(edges.begin(), edges.end(), compEdge);
    ans = 0;
    
    unionFind town(n);
    auto cur = --edges.begin();
    for (int cnt=0; cnt<n-1;) {
        ++cur;
        
        if (town.find(cur->a) == town.find(cur->b)) continue;
        
        town.merge(cur->a, cur->b);
        ans += cur->cost;
        ++cnt;
    }
    
    cout << ans - cur->cost;
    
    return 0;
}
