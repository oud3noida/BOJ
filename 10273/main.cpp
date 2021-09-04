#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

constexpr int UNDEFINED = numeric_limits<int>::min();
int tests, num_caves, num_paths, max_accumulated, optimal_cave;
vector<int> reward, num_parents, cur_accumulated, optimal_parent;
vector<vector<pair<int, int>>> children;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    
    for (int t = 0; t < tests; t++) {
        cin >> num_caves >> num_paths;
        
        reward.assign(num_caves, 0);
        cur_accumulated.assign(num_caves, UNDEFINED);
        for (int i = 0; i < num_caves; i++) {
            cin >> reward[i];
        }
        
        num_parents.assign(num_caves, 0);
        children.assign(num_caves, vector<pair<int, int>>());
        int a, b, c;
        for (int i = 0; i < num_paths; i++) {
            cin >> a >> b >> c;
            children[a - 1].emplace_back(b - 1, c);
            ++num_parents[b - 1];
        }
        
        optimal_parent.assign(num_caves, -1);
        cur_accumulated[0] = reward[0];
        max_accumulated = UNDEFINED;
        queue<int> q;
        q.push(0);
        
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            if (max_accumulated < cur_accumulated[cur]) {
                max_accumulated = cur_accumulated[cur];
                optimal_cave = cur;
            }
            
            for (auto [child, cost] : children[cur]) {
                --num_parents[child];
                int gross = cur_accumulated[cur] - cost + reward[child];
                if (cur_accumulated[child] < gross) {
                    cur_accumulated[child] = gross;
                    optimal_parent[child] = cur;
                }
                
                if (num_parents[child] == 0) {
                    q.push(child);
                }
            }
        }
        
        vector<int> optimal_path;
        optimal_path.push_back(optimal_cave);
        
        while (optimal_parent[optimal_path.back()] != -1) {
            optimal_path.push_back(optimal_parent[optimal_path.back()]);
        }
        
        cout << max_accumulated << ' ' << optimal_path.size() << '\n';
        for (auto it = optimal_path.rbegin(); it != optimal_path.rend(); ++it) {
            cout << *it + 1 << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
