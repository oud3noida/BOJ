#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 32000;
int n, m;
int numParent[N];
vector<int> child[N];
int topoIdx[N];

void topoSort() {
    queue<int> q;
    int top = 0;
    
    for (int i=0; i<n; i++) {
        if (!numParent[i]) q.push(i);
    }
    
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int c=0; c<child[cur].size(); c++) {
            numParent[child[cur][c]] -= 1;
            if (!numParent[child[cur][c]]) q.push(child[cur][c]);
        }
        topoIdx[top++] = cur+1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    for (int i=0; i<n; i++) numParent[i] = 0;
    
    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        numParent[b-1] += 1;
        child[a-1].push_back(b-1);
    }
    
    topoSort();
    
    for (int i=0; i<n; i++) cout << topoIdx[i] << " ";
    
    return 0;
}
