#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int num_chickens, num_cows;
multiset<int> chickens;
vector<pair<int, int>> cows;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_chickens >> num_cows;
    
    int t;
    for (int i = 0; i < num_chickens; i++) {
        cin >> t;
        chickens.insert(t);
    }
    
    int a, b;
    for (int i = 0; i < num_cows; i++) {
        cin >> a >> b;
        cows.emplace_back(a, b);
    }
    sort(cows.begin(), cows.end(),
         [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
             return lhs.second < rhs.second;
         });
    
    int helped = 0;
    for (int i = 0; i < num_cows; i++) {
        auto [a, b] = cows[i];
        auto helper = chickens.lower_bound(a);
        if (helper != chickens.end() && *helper <= b) {
            chickens.erase(helper);
            ++helped;
        }
    }
    
    cout << helped;
    
    return 0;
}
