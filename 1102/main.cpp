#include <iostream>
#include <vector>

using namespace std;

int N, target_num_plant;
vector<vector<int>> cost;
vector<int> min_cost_cache;

int min(const int &a, const int &b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return (a < b) ? a : b;
}

int min_cost(int cur_state, int cur_num_plant) {
    if (cur_num_plant >= target_num_plant) return 0;
    
    int &ret = min_cost_cache[cur_state];
    if (ret != -1) return ret;
    
    for (int from=0; from<N; ++from) {
        if (!(cur_state & (1<<from))) continue;
        
        for (int to=0; to<N; ++to) {
            if (cur_state & (1<<to)) continue;
            
            ret = min(ret, min_cost(cur_state | (1<<to), cur_num_plant + 1) + cost[from][to]);
        }
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N;
    
    cost.assign(N, vector<int>(N, 0));
    min_cost_cache.assign(1<<N, -1);
    for (int from=0; from<N; ++from) {
        for (int to=0; to<N; ++to) {
            cin >> cost[from][to];
        }
    }
    
    int initial_state = 0, initial_num_plant = 0;
    char plant_state;
    for (int i=0; i<N; ++i) {
        cin >> plant_state;
        if (plant_state == 'Y') {
            initial_state |= (1<<i);
            initial_num_plant += 1;
        }
    }
    
    cin >> target_num_plant;
    
    cout << min_cost(initial_state, initial_num_plant);
}
