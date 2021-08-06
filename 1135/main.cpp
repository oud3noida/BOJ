#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 100;
int n;
vector<int> parent, cache;
vector<vector<int>> children;

int find_min_pipeline(int cur) {
    int &ret = cache[cur];
    if (ret != -1) return ret;
    
    int num_children = children[cur].size();
        
    vector<int> children_time;
    for (int &c : children[cur]) {
        children_time.push_back(find_min_pipeline(c) + 1);
    }
    sort(children_time.rbegin(), children_time.rend());
    
    for (int i=0; i<num_children; ++i) {
        ret = max(ret, children_time[i] + i);
    }
    if (ret == -1) ret = 0;
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    parent.assign(n, -1);
    children.assign(n, vector<int>());
    cache.assign(n, -1);
    for (int i=0; i<n; ++i) {
        cin >> parent[i];
        if (parent[i] >= 0) {
            children[parent[i]].push_back(i);
        }
    }
    
    cout << find_min_pipeline(0);
    
    return 0;
}
