#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E, totalCost;
vector<pair<int, pair<int, int>>> edges; // (cost, end1, end2)

class unionFind {
    private:
    int parent[10000], rank[10000];
    
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
        edges.push_back(make_pair(c, make_pair(a-1, b-1)));
    }
    sort(edges.begin(), edges.end());
    
    unionFind vertices(V);
    totalCost = 0;
    auto e = edges.begin();
    for (int cnt=0; cnt<V-1;) {
        a = e->second.first;
        b = e->second.second;
        c = e->first;
        ++e;
        
        if (vertices.find(a) == vertices.find(b)) continue;
        
        vertices.merge(a, b);
        totalCost += c;
        cnt++;
    }
    
    cout << totalCost;
    
    return 0;
}
