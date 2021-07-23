#include <iostream>
#include <vector>

using namespace std;

const int NONE = 0;
int num_edges, num_vertices;
vector<int> parent, num_child;

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    
    if (num_child[a] > num_child[b]) {
        parent[b] = a;
        ++num_child[a];
    } else {
        parent[a] = b;
        ++num_child[b];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> num_edges >> num_vertices;
    
    for (int i=0; i<num_edges; ++i) {
        parent.emplace_back(i);
    }
    num_child.assign(num_edges, 0);
    
    int u, v;
    int game_over_turn = 0;
    for (int i=0; i<num_vertices; ++i) {
        cin >> u >> v;
        
        if (find(u) == find(v)) {
            game_over_turn = i+1;
            break;
        }
        
        merge(u, v);
    }
    
    cout << game_over_turn;
    
    return 0;
}
