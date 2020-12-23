#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX = 9;
int n;
vector<int> num_parent_original;
vector<vector<int>> children;
vector<int> max_ans, min_ans;

void max_topo(int cur) {
    vector<int> num_parent(num_parent_original);

    set<int> q;
    for (int i=0; i<n; ++i) if (num_parent[i] == 0) q.insert(i);

    for (int i=0; i<n; ++i) {
        int par = *(--q.end());
        q.erase(--q.end());
        for (int chi : children[par]) {
            if (--num_parent[chi] == 0) q.insert(chi);
        }
        max_ans[par] = i + (MAX - n + 1);
    }
}

void min_topo(int cur) {
    vector<int> num_parent(num_parent_original);

    set<int> q;
    for (int i=0; i<n; ++i) if (num_parent[i] == 0) q.insert(i);

    for (int i=0; i<n; ++i) {
        int par = *(q.begin());
        q.erase(q.begin());
        for (int chi : children[par]) {
            if (--num_parent[chi] == 0) q.insert(chi);
        }
        min_ans[par] = i;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    ++n;
    num_parent_original.assign(n, 0);
    children.assign(n, vector<int>());

    int par, chi;
    char c;
    for (int i=1; i<n; ++i) {
        cin >> c;
        if (c == '<') {par = i-1; chi = i;}
        else {par = i; chi = i-1;}

        children[par].push_back(chi);
        ++num_parent_original[chi];
    }

    max_ans.assign(n, 0);
    min_ans.assign(n, 0);
    max_topo(0);
    min_topo(0);

    for (int x : max_ans) cout << x;
    cout << "\n";
    for (int x : min_ans) cout << x;

    return 0;
}