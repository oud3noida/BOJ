#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int cost, a, b;
    
    edge(int c, int i, int j) : cost(c), a(i), b(j) {}
};

bool operator<(edge const& a, edge const& b) {
    return a.cost < b.cost;
}

const int MAX = 10000;
int V, E, totalCost;
vector<edge> edges;

class unionFind {
    private:
    int parent[MAX], rank[MAX];
    
    public:
    unionFind(int size) {
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
    }
    
    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> V >> E;
    int a, b, c;
    for (int i=0; i<E; i++) {
        cin >> a >> b >> c;
        edges.push_back(edge(c, a-1, b-1));
    }
    sort(edges.begin(), edges.end());
    
    unionFind vertices(V);
    totalCost = 0;
    auto cur = --edges.begin();
    for (int cnt=0; cnt<V-1;) {
        ++cur;
        
        if (vertices.find(cur->a) == vertices.find(cur->b)) continue;
        
        vertices.merge(cur->a, cur->b);
        totalCost += cur->cost;
        cnt++;
    }
    
    cout << totalCost;
    
    return 0;
}
