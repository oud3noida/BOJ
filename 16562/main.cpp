#include <iostream>
#include <algorithm>

using namespace std;

struct edge {
    int student, cost;
    edge() : student(0), cost(0) {}
};

bool operator<(edge a, edge b) {
    return a.cost < b.cost;
}

const int MAX = 10000, ME = 0;
int n, m, budget, money;
edge E[MAX+1];

class unionFind {
    private:
    int parent[MAX+1], rank[MAX+1];
    
    public:
    unionFind(int size) {
        for (int i=0; i<size; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    
    void befriend(int a, int b) {
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
    
    cin >> n >> m >> budget;
    money = 0;
    
    for (int i=1; i<=n; i++) {
        E[i].student = i;
        cin >> E[i].cost;
    }
    sort(E, E+(n+1));
    
    unionFind students(n+1);
    int v, w, cnt = 0;
    for (int i=0; i<m; i++) {
        cin >> v >> w;
        if (students.find(v) != students.find(w)) {
            students.befriend(v, w);
            cnt++;
        }
    }
    
    int cur = 0;
    while (cnt < n) {
        ++cur;
        
        if (students.find(ME) == students.find(E[cur].student)) continue;
        
        students.befriend(ME, E[cur].student);
        money += E[cur].cost;
        
        ++cnt;
    }
    
    if (money <= budget) cout << money;
    else cout << "Oh no";
    
    return 0;
}
