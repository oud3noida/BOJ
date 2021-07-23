#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, num_priorities;
vector<int> num_parents;
vector<vector<int>> child;
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> num_priorities;
    
    num_parents.assign(n, 0);
    child.assign(n, vector<int>());
    
    int a, b;
    for (int i=0; i<num_priorities; ++i) {
        cin >> a >> b;
        ++num_parents[b-1];
        child[a-1].emplace_back(b-1);
    }
    
    for (int i=0; i<n; ++i) {
        if (num_parents[i] == 0) {
            pq.push(i);
        }
    }
    
    while (!pq.empty()) {
        int cur = pq.top();
        pq.pop();
        
        cout << cur+1 << " ";
        
        for (int cur_child : child[cur]) {
            if (--num_parents[cur_child] == 0)
                pq.push(cur_child);
        }
    }
    
    return 0;
}
