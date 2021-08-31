#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

constexpr int INF = 1'999'999'999,
              MAX = 1'000'000'000;
int num_vertices, num_edges;
vector<multimap<int, int>> cost;
int factory_from, factory_to;

bool traverse(int min_cost) {
    vector<bool> visited(num_vertices, false);
    queue<int> q;
    visited[factory_from] = true;
    q.push(factory_from);
    
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        
        for (auto to = cost[from].lower_bound(min_cost);
             to != cost[from].end(); ++to) {
            if (visited[to->second]) continue;
            if (to->second == factory_to) return true;
            visited[to->second] = true;
            q.push(to->second);
        }
    }
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_vertices >> num_edges;
    
    cost.assign(num_vertices, multimap<int, int>());
    int a, b, c;
    for (int i = 0; i < num_edges; i++) {
        cin >> a >> b >> c;
        cost[a-1].emplace(c, b-1);
        cost[b-1].emplace(c, a-1);
    }
    cin >> factory_from >> factory_to;
    --factory_from;
    --factory_to;
    
    int cost_left = 1, cost_right = MAX;
    int ans = 1;
    while (cost_left <= cost_right) {
        int cost_mid = (cost_left + cost_right) / 2;
        if (traverse(cost_mid)) {
            ans = cost_mid;
            cost_left = cost_mid + 1;
        } else {
            cost_right = cost_mid - 1;
        }
    }
    
    cout << ans;
    
    return 0;
}
