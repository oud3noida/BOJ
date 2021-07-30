#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int MAX = 1000;
vector<vector<vector<bool>>> visited;
queue<vector<int>> q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    visited.assign(MAX+1, vector<vector<bool>>(MAX+1, vector<bool>(MAX+1, false)));
    
    vector<int> init(3, 0);
    for (int i=0; i<3; ++i) {
        cin >> init[i];
    }
    sort(init.begin(), init.end());
    
    q.emplace(init);
    visited[init[0]][init[1]][init[2]] = true;
    
    while (!q.empty()) {
        vector<int> cur(q.front());
        q.pop();
        
        if (cur[0] == cur[1] && cur[1] == cur[2]) {
            cout << 1;
            return 0;
        }
        
        for (int i=0; i<2; ++i) {
            for (int j=i+1; j<3; ++j) {
                vector<int> next(cur);
                
                next[j] -= next[i];
                next[i] *= 2;
                sort(next.begin(), next.end());
                
                if (next[2] > MAX) continue;
                
                if (!visited[next[0]][next[1]][next[2]]) {
                    q.emplace(next);
                    visited[next[0]][next[1]][next[2]] = true;
                }
            }
        }
    }
    
    cout << 0;
    
    return 0;
}
