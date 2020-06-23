#include <iostream>
#include <assert.h>

using namespace std;

const int MAX = 1000000;
int X, Y, ans;

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

int adjZone(int x, int y, char dir) {
    switch (dir) {
        case 'U': return (y-1)*X + x;
        case 'D': return (y+1)*X + x;
        case 'L': return y*X + (x-1);
        case 'R': return y*X + (x+1);
    }
    
    // ERROR
    assert(true);
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X;
    ans = X*Y;
    
    unionFind zone(X*Y);
    string cells;
    for (int y=0; y<Y; y++) {
        cin >> cells;
        for (int x=0; x<X; x++) {
            int a = y*X + x,
                b = adjZone(x, y, cells[x]);
            
            if (zone.find(a) == zone.find(b)) continue;
            
            zone.merge(a, b);
            --ans;
        }
    }
    
    cout << ans;
    
    return 0;
}
