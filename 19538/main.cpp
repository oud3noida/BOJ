#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, t;
vector<vector<int>> adj;
vector<int> numBeliever, threshold, rumorTime;
queue<pair<int, int>> q;

void spreadRumor() {
    vector<bool> visited(N, false);
    
    while (!q.empty()) {
        int t = q.front().first;
        int cur = q.front().second;
        q.pop();
        
        if (rumorTime[cur] != -1) continue;
        rumorTime[cur] = t;
        for (int neighbor : adj[cur]) {
            if (rumorTime[neighbor] != -1) continue;
            ++numBeliever[neighbor];
            if (!visited[neighbor] && numBeliever[neighbor] >= threshold[neighbor]) {
                visited[neighbor] = true;
                q.push(make_pair(t+1, neighbor));
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    adj.assign(N, vector<int>());
    numBeliever.assign(N, 0);
    threshold.assign(N, 0);
    rumorTime.assign(N, -1);
    
    int x;
    for (int i=0; i<N; ++i) {
        x = -1;
        int cnt = -1;
        do {
            cin >> x;
            ++cnt;
            if (x != 0) adj[i].push_back(x-1);
        } while (x != 0);
        if (cnt % 2 == 0) threshold[i] = cnt / 2;
        else threshold[i] = (cnt + 1) / 2;
    }
    
    cin >> M;
    for (int i=0; i<M; ++i) {
        cin >> x;
        q.push(make_pair(0, x-1));
    }
    
    spreadRumor();
    
    for (int i=0; i<N; ++i) cout << rumorTime[i] << " ";
    
    return 0;
}
