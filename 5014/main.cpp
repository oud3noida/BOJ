#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<bool> visited;
queue<pair<int, int>> q;
int F, S, G, U, D;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> F >> S >> G >> U >> D;
    
    visited.assign(F, false);
    q.push(make_pair(0, S-1));
    visited[S-1] = true;
    
    while (!q.empty()) {
        int cur = q.front().second;
        int ans = q.front().first;
        q.pop();
        
        if (cur == G-1) {
            cout << ans;
            return 0;
        }
        
        if (cur+U < F && !visited[cur+U]) {
            q.push(make_pair(ans+1, cur+U));
            visited[cur+U] = true;
        }
        if (cur-D >= 0 && !visited[cur-D]) {
            q.push(make_pair(ans+1, cur-D));
            visited[cur-D] = true;
        }
    }
    
    cout << "use the stairs";
    
    return 0;
}
