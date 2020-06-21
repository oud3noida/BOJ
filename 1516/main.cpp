#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 500, INF = 987654321;
int n;
int cost[MAX], numParent[MAX], topoIdx[MAX];
vector<int> child[MAX], parent[MAX];
queue<int> q;

int maxCost(vector<int>& v) {
    int ret = 0;
    for (auto i = v.begin(); i != v.end(); i++) {
        ret = max(ret, cost[*i]);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int tmp;
    for (int i=0; i<n; i++) {
        cin >> cost[i] >> tmp;
        numParent[i] = 0;
        while (tmp != -1) {
            numParent[i]++;
            parent[i].push_back(tmp-1);
            child[tmp-1].push_back(i);
            cin >> tmp;
        }
        if (!numParent[i]) q.push(i);
    }
    
    // Topological sort
    int idx = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto c = child[cur].begin(); c != child[cur].end(); c++) {
            numParent[*c]--;
            if (!numParent[*c]) q.push(*c);
        }
        topoIdx[idx++] = cur;
    }
    
    for (int i=0; i<n; i++) {
        if (!parent[topoIdx[i]].size()) continue;
        cost[topoIdx[i]] += maxCost(parent[topoIdx[i]]);
    }
    
    for (int i=0; i<n; i++) cout << cost[i] << "\n";
    
    return 0;
}
