#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct planet {
    int x, y, z, idx;
    planet(int i, int j, int k, int n) : x(i), y(j), z(k), idx(n) {}
};

bool xComp(planet const& lhs, planet const& rhs) {
    return lhs.x < rhs.x;
}

bool yComp(planet const& lhs, planet const& rhs) {
    return lhs.y < rhs.y;
}

bool zComp(planet const& lhs, planet const& rhs) {
    return lhs.z < rhs.z;
}

struct tunnel {
    int a, b, cost;
    tunnel(planet i, planet j, int c) : a(i.idx), b(j.idx), cost(c) {}
};

bool operator<(tunnel const& lhs, tunnel const& rhs) {
    return lhs.cost < rhs.cost;
}

const int MAX = 100000;
int n;
long long ans;
vector<planet> planets;
vector<tunnel> edges;

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
    
    cin >> n;
    
    int x, y, z;
    for (int i=0; i<n; i++) {
        cin >> x >> y >> z;
        planets.push_back(planet(x, y, z, i));
    }
    
    sort(planets.begin(), planets.end(), xComp);
    for (int i=1; i<n; i++)
        edges.push_back(tunnel(planets[i-1], planets[i], abs(planets[i-1].x - planets[i].x)));
    
    sort(planets.begin(), planets.end(), yComp);
    for (int i=1; i<n; i++)
        edges.push_back(tunnel(planets[i-1], planets[i], abs(planets[i-1].y - planets[i].y)));
    
    sort(planets.begin(), planets.end(), zComp);
    for (int i=1; i<n; i++)
        edges.push_back(tunnel(planets[i-1], planets[i], abs(planets[i-1].z - planets[i].z)));
    
    sort(edges.begin(), edges.end());
    
    ans = 0;
    unionFind universe(n);
    auto cur = edges.begin();
    for (int cnt=0; cnt<n-1; ++cur) {
        if (universe.find(cur->a) == universe.find(cur->b)) continue;
        
        universe.merge(cur->a, cur->b);
        ans += cur->cost;
        ++cnt;
    }
    cout << ans;
    
    return 0;
}
