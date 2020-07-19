#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n, m, idx_t, idx_scc;
vector<int> treeIdx, sccIdx, ansSAT;
vector<vector<int>> adj;
stack<int> visited, topoReverse;

int graphIdx(int x) {
    return (x > 0) ? (-1+x)*2 : (-1-x)*2 + 1;
}

int neg(int x) {
    return (x%2 == 0) ? x+1 : x-1;
}

int _findSCC(int cur) {
    int ret = treeIdx[cur] = idx_t++;
    visited.push(cur);
    for (int &next : adj[cur]) {
        if (treeIdx[next] == -1)
            ret = min(ret, _findSCC(next));
        else if (sccIdx[next] == -1)
            ret = min(ret, treeIdx[next]);
    }
    
    if (ret == treeIdx[cur]) {
        int i;
        do {
            i = visited.top(); visited.pop();
            sccIdx[i] = idx_scc;
            topoReverse.push(i);
        } while (i != cur);
        ++idx_scc;
    }
    
    return ret;
}

void findSCC() {
    idx_t = 0;
    idx_scc = 0;
    treeIdx.assign(2*n, -1);
    sccIdx.assign(2*n, -1);
    for (int i=0; i<2*n; ++i) {
        if (treeIdx[i] == -1) _findSCC(i);
    }
}

void solve2SAT() {
    findSCC();
    
    for (int i=0; i<2*n; i+=2) {
        if (sccIdx[i] == sccIdx[i+1]) return;
    }
    
    ansSAT.assign(n, -1);
    
    while (!topoReverse.empty()) {
        int cur = topoReverse.top() / 2,
            val = topoReverse.top() % 2;
        topoReverse.pop();
        
        if (ansSAT[cur] == -1) ansSAT[cur] = val;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    
    adj.assign(2*n, vector<int>());
    int a, b;
    for (int i=0; i<m; ++i) {
        cin >> a >> b;
        adj[neg(graphIdx(a))].push_back(graphIdx(b));
        adj[neg(graphIdx(b))].push_back(graphIdx(a));
    }
    
    solve2SAT();
    
    if (!ansSAT.empty()) {
        cout << "1\n";
        for (int &v : ansSAT) cout << v << " ";
    } else cout << 0;
    
    return 0;
}
