#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1000;
int T, n, k, x, y, w;
int cost[MAX];
vector<int> parent[MAX], child[MAX];
int topoIdx[MAX];

void topoSort() {
    queue<int> q;
    int numParent[MAX];
    int top = 0;
    
    for (int i=0; i<n; i++) {
        if (parent[i].empty()) q.push(i);
        numParent[i] = parent[i].size();
    }
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for (int c=0; c<child[cur].size(); c++) {
            numParent[child[cur][c]] -= 1;
            if (numParent[child[cur][c]] == 0) q.push(child[cur][c]);
        }
        
        topoIdx[top++] = cur;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    
    for (int t=0; t<T; t++) {
        cin >> n >> k;
        
        for (int i=0; i<n; i++) {
            cin >> cost[i];
            parent[i].clear();
            child[i].clear();
        }
        
        for (int i=0; i<k; i++) {
            cin >> x >> y;
            parent[y-1].push_back(x-1);
            child[x-1].push_back(y-1);
        }
        
        topoSort();
        
        cin >> w;
        
        for (int i=0; i<n; i++) {
            int maxPrevCost = 0;
            for (int p=0; p<parent[topoIdx[i]].size(); p++) {
                maxPrevCost = max(maxPrevCost, cost[parent[topoIdx[i]][p]]);
            }
            cost[topoIdx[i]] += maxPrevCost;
        }
        
        cout << cost[w-1] << endl;
    }
    
    return 0;
}
