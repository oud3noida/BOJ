#include <iostream>
#include <vector>

using namespace std;

int n, num_boots;
vector<int> snow;
vector<pair<int, int>> boots_bag;
vector<vector<int>> cache;

void step_on_tile(int tile, int boots) {
    if (tile == n) return;
    if (cache[tile][boots] != -1) return;
    
    if (boots_bag[boots - 1].first < snow[tile]) {
        cache[tile][boots] = 0;
        return;
    } else {
        cache[tile][boots] = 1;
    }
    
    for (int next_boots = max(boots, 1); next_boots <= num_boots; next_boots++) {
        int next_depth = boots_bag[next_boots - 1].first;
        int next_step = boots_bag[next_boots - 1].second;
        if (next_depth < snow[tile]) continue;
        
        for (int next_tile = tile + 1; next_tile <= min(tile + next_step, n); next_tile++) {
            step_on_tile(next_tile, next_boots);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_boots;
    
    snow.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> snow[i];
    }
    
    for (int i = 0; i < num_boots; i++) {
        int depth, step;
        cin >> depth >> step;
        boots_bag.emplace_back(depth, step);
    }
    
    cache.assign(n, vector<int>(num_boots + 1, -1));
    step_on_tile(0, 0);
    
    for (int i = 1; i <= num_boots; i++) {
        if (cache[n-1][i] == 1) {
            cout << i-1;
            break;
        }
    }
    
    return 0;
}
