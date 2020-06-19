#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1987654321, MAX = 100000;
int n, k;
vector<int> times, prevIdx;
queue<int> q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    times.assign(MAX+1, INF);
    prevIdx.assign(MAX+1, -1);
    
    times[n] = 0;
    q.push(n);
    
    // Find shortest route
    while (!q.empty() && times[k] == INF) {
        int cur = q.front();
        q.pop();
        
        if (cur > 0 && times[cur-1] > times[cur]+1) {
            times[cur-1] = times[cur]+1;
            prevIdx[cur-1] = cur;
            q.push(cur-1);
        }
        if (cur < MAX && times[cur+1] > times[cur]+1) {
            times[cur+1] = times[cur]+1;
            prevIdx[cur+1] = cur;
            q.push(cur+1);
        }
        if (cur*2 <= MAX && times[cur*2] > times[cur]+1) {
            times[cur*2] = times[cur]+1;
            prevIdx[cur*2] = cur;
            q.push(cur*2);
        }
    }
    
    cout << times[k] << "\n";
    
    // Backtrack the route
    vector<int> goBackwards;
    while (k >= 0) {
        goBackwards.push_back(k);
        k = prevIdx[k];
    }
    
    for (int i=goBackwards.size()-1; i>=0; i--) {
        cout << goBackwards[i] << " ";
    }
    
    return 0;
}
