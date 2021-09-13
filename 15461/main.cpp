#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

constexpr int MAX = 1'000'000'000;
int n, initial_milk, ans;
vector<pair<int, pair<int, int>>> queries;
map<int, int> milk_from;
map<int, set<int>> cows_outputing;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> initial_milk;
    
    for (int i = 0; i < n; i++) {
        int day, cow, milk;
        cin >> day >> cow >> milk;
        queries.emplace_back(day, make_pair(cow, milk));
    }
    sort(queries.begin(), queries.end());
    
    cows_outputing[0].insert(0);
    int prev_max_milk = 0;
    int prev_max_cows = 1;
    int prev_max_only_cow = 0;
    
    ans = 0;
    for (auto query : queries) {
        auto [cow, milk] = query.second;
        int prev_milk = milk_from[cow];
        
        if (prev_milk > 0) {
            cows_outputing[prev_milk].erase(cow);
            if (cows_outputing[prev_milk].size() == 0) {
                cows_outputing.erase(prev_milk);
            }
        }
        
        milk += prev_milk;
        milk_from[cow] = milk;
        if (milk > 0) {
            cows_outputing[milk].insert(cow);
        }
        
        int cur_max_milk = cows_outputing.rbegin()->first;
        int cur_max_cows = cows_outputing[cur_max_milk].size();
        
        if (prev_max_milk == cur_max_milk && prev_max_cows == cur_max_cows) {
            if (cur_max_milk == 0 && milk < 0) {
                ++ans;
            }
            continue;
        }
        
        int cur_max_only_cow = 0;
        if (cur_max_cows == 1) {
            cur_max_only_cow = *cows_outputing[cur_max_milk].begin();
        }
        
        if (prev_max_cows != cur_max_cows ||
            (cur_max_cows == 1 && prev_max_only_cow != cur_max_only_cow)) {
            ++ans;
        }
        
        prev_max_milk = cur_max_milk;
        prev_max_cows = cur_max_cows;
        prev_max_only_cow = cur_max_only_cow;
    }
    
    cout << ans;
    
    return 0;
}
