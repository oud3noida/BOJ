#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct jewel {
    int weight, value;
    jewel(int w, int v) : weight(w), value(v) {}
};

bool operator<(jewel const& lhs, jewel const& rhs) {
    return lhs.value < rhs.value;
}

int n, k;
long long ans;
multiset<int> bags;
vector<jewel> jewels;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    
    int w, v;
    for (int i=0; i<n; i++) {
        cin >> w >> v;
        jewels.push_back(jewel(w, v));
    }
    for (int i=0; i<k; i++) {
        cin >> w;
        bags.insert(w);
    }
    sort(jewels.begin(), jewels.end());
    
    ans = 0;
    for (auto j=--jewels.end(); j!=--jewels.begin(); --j) {
        if (bags.empty()) break;
        
        auto b = bags.lower_bound(j->weight);
        if (b == bags.end()) continue;
        bags.erase(b);
        ans += j->value;
    }
    
    cout << ans;
    
    return 0;
}
