#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1987654321, MAX = 100000;
int n, k;
vector<int> times;
queue<int> q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    times.assign(MAX+1, INF);
    
    times[n] = 0;
    q.push(n);
    
    // Find shortest route
    while (!q.empty() && times[k] == INF) {
        int cur = q.front();
        q.pop();
        
        if (cur > 0 && times[cur-1] > times[cur]+1) {
            times[cur-1] = times[cur]+1;
            q.push(cur-1);
        }
        if (cur < MAX && times[cur+1] > times[cur]+1) {
            times[cur+1] = times[cur]+1;
            q.push(cur+1);
        }
        if (cur*2 <= MAX && times[cur*2] > times[cur]) {
            times[cur*2] = times[cur];
            q.push(cur*2);
        }
    }
    
    cout << times[k] << "\n";
    
    return 0;
}
