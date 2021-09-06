#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

constexpr int MAX = 200;
vector<int> max_water;
vector<vector<vector<bool>>> visited;
queue<vector<int>> q;
set<int> ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    max_water.assign(3, 0);
    for (int i = 0; i < 3; ++i) {
        cin >> max_water[i];
    }
    
    visited.assign(MAX+1, vector<vector<bool>>(MAX+1, vector<bool>(MAX+1, false)));
    q.push({0, 0, max_water[2]});
    visited[0][0][max_water[2]] = true;
    
    while (!q.empty()) {
        auto cur_water = q.front();
        q.pop();
        
        if (cur_water[0] == 0) ans.emplace(cur_water[2]);
        
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;
                
                if (cur_water[from] > 0 && cur_water[to] < max_water[to]) {
                    int water = min(cur_water[from], max_water[to] - cur_water[to]);
                    
                    vector<int> next_water = cur_water;
                    next_water[from] -= water;
                    next_water[to] += water;
                    
                    if (!visited[next_water[0]][next_water[1]][next_water[2]]) {
                        visited[next_water[0]][next_water[1]][next_water[2]] = true;
                        q.push(next_water);
                    }
                }
            }
        }
    }
    
    for (int answer : ans) {
        cout << answer << ' ';
    }
    
    return 0;
}
