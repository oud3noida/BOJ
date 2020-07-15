#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAX_V = 100000;
int v, e, idx_t;
int treeIdx[MAX_V];
vector<int> adj[MAX_V];
vector<pair<int, int>> ans;

int findCutEdge(int prev, int cur) {
    int ret = treeIdx[cur] = idx_t++;
    for (int &next : adj[cur]) {
        if (next == prev) continue;
        
        if (treeIdx[next] != -1) {
            ret = min(ret, treeIdx[next]);
            continue;
        }
        
        int subtree = findCutEdge(cur, next);
        ret = min(ret, subtree);
    }
    
    if (prev != -1 && ret >= treeIdx[cur]) {
        if (prev < cur) ans.push_back(make_pair(prev, cur));
        else ans.push_back(make_pair(cur, prev));
    }
    
    return ret; 
}

bool operator<(pair<int, int> &a, pair<int, int> &b) {
    if (a.first != b.first) a.first < b.first;
    else a.second < b.second;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> v >> e;
    
    int a, b;
    for (int i=0; i<e; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    
    fill_n(treeIdx, v, -1);
    idx_t = 0;
    for (int i=0; i<v; ++i) {
        if (treeIdx[i] != -1) continue;
        findCutEdge(-1, i);
    }
    
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto &a : ans) cout << a.first+1 << " " << a.second+1 << "\n";
    
    return 0;
}
