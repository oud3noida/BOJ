#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<long long, long long> Segment;
typedef pair<long long, int> Mask;

bool compBoth(Segment a, Segment b) {
    return (a.first != b.first) ? a.first < b.first : a.second < b.second;
}

struct classcomp {
    bool operator()(const Segment& a, const Segment& b) const {
        return a.second < b.second;
    }
};

int numCitizen, numStore, ans;
vector<Segment> citizens;
multiset<Segment, classcomp> customers;
vector<Mask> stores;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> numCitizen >> numStore;
    ans = 0;
    
    long long a, b;
    for (int i=0; i<numCitizen; ++i) {
        cin >> a >> b;
        citizens.push_back(make_pair(a, b));
    }
    sort(citizens.begin(), citizens.end(), compBoth);
    
    int c;
    for (int i=0; i<numStore; ++i) {
        cin >> a >> c;
        stores.push_back(make_pair(a, c));
    }
    sort(stores.begin(), stores.end());
    
    auto curCitizen = citizens.begin();
    for (auto curMask : stores) {
        long long costMask = curMask.first;
        int numMask = curMask.second;
        
        while (!customers.empty() && costMask > customers.begin()->second) {
            customers.erase(customers.begin());
        }
        
        for (; curCitizen != citizens.end(); ++curCitizen) {
            if (curCitizen->first > costMask) break;
            if (costMask > curCitizen->second) continue;
            customers.insert(*curCitizen);
        }
        
        while (!customers.empty()) {
            if (numMask-- <= 0) break;
            customers.erase(customers.begin());
            ++ans;
        }
    }
    
    cout << ans;
    
    return 0;
}
