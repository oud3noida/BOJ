#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int v, e, idx_t;
vector<vector<int>> adj, ssc;
vector<int> treeIdx;
stack<int> visited;
vector<bool> isInSSC;

bool operator<(vector<int> &a, vector<int> &b) {
    return a.front() < b.front();
}

int findSSC(int cur) {
    int ret = treeIdx[cur] = idx_t++;
    visited.push(cur);
    for (int &next : adj[cur]) {
        if (cur == next) continue;
        if (treeIdx[next] == -1)
            ret = min(ret, findSSC(next));
        else if (!isInSSC[next])
            ret = min(ret, treeIdx[next]);
    }
    
    if (ret >= treeIdx[cur]) {
        ssc.push_back(vector<int>());
        int i = -1;
        do {
            i = visited.top(); visited.pop();
            isInSSC[i] = true;
            (--ssc.end())->push_back(i);
        } while (i != cur);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> v >> e;
    adj.assign(v, vector<int>());
    
    int a, b;
    for (int i=0; i<e; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
    }
    
    idx_t = 0;
    treeIdx.assign(v, -1);
    isInSSC.assign(v, false);
    for (int i=0; i<v; ++i) {
        if (treeIdx[i] == -1) findSSC(i);
    }
    
    for (int c=0; c<ssc.size(); ++c)
        sort(ssc[c].begin(), ssc[c].end());
    sort(ssc.begin(), ssc.end());
    
    cout << ssc.size() << "\n";
    for (auto &c : ssc) {
        for (int &x : c)
            cout << x+1 << " ";
        cout << "-1\n";
    }
    
    return 0;
}
