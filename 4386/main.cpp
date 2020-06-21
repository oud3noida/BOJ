#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct pos {
    double x, y;
    
    pos() : x(0), y(0) {}
};

struct edge {
    double cost;
    int a, b;
    
    edge(double c, int i, int j) : cost(c), a(i), b(j) {}
};

bool operator< (edge const& lhs, edge const& rhs) {
    return lhs.cost < rhs.cost;
}

const int MAX = 100;
int n;
double ans;
pos star[MAX];
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

double dst(pos& a, pos& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> star[i].x >> star[i].y;
        for (int j=0; j<i; j++) {
            edges.push_back(edge(dst(star[i], star[j]), i, j));
        }
    }
    sort(edges.begin(), edges.end());
    
    unionFind starSet(n);
    ans = 0.0;
    auto cur = --edges.begin();
    for (int cnt=0; cnt<n-1;) {
        ++cur;
        
        if (starSet.find(cur->a) == starSet.find(cur->b)) continue;
        
        starSet.merge(cur->a, cur->b);
        ans += cur->cost;
        cnt++;
    }
    
    cout << ans;
    
    return 0;
}
