#include <iostream>
#include <vector>
#include <stack>

using namespace std;

constexpr int NOT_VISITED = -1,
              VISITING = 0,
              COMPLETE = 1;
int n, ans;
vector<int> adj, visited;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    adj.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> adj[i];
    }
    
    visited.assign(n, NOT_VISITED);
    ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (visited[i] != NOT_VISITED) continue;
        int cur = i;
        stack<int> stk;
        
        while (visited[cur] == NOT_VISITED) {
            visited[cur] = VISITING;
            stk.push(cur);
            cur = adj[cur] - 1;
        }
        
        if (visited[cur] == VISITING) {
            while (stk.top() != cur) {
                visited[stk.top()] = COMPLETE;
                ++ans;
                stk.pop();
            }
            visited[stk.top()] = COMPLETE;
            ++ans;
            stk.pop();
        }
        
        while (!stk.empty()) {
            visited[stk.top()] = COMPLETE;
            stk.pop();
        }
    }
    
    cout << ans;
    
    return 0;
}
