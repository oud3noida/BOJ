#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;
vector<vector<int>> adj;
vector<int> parent, num_child;

void memo_parent(int par, int cur) {
    parent[cur] = par;
    for (int child : adj[cur]) {
        if (parent[child] != -1) continue;
        memo_parent(cur, child);
        ++num_child[cur];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    adj.assign(N, vector<int>());
    int a, b;
    for (int i=0; i<N-1; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    parent.assign(N, -1);
    num_child.assign(N, 0);

    memo_parent(0, 0);

    stack<int> stk;
    stk.push(0);

    cin >> a;
    if (a != 1) {
        cout << 0;
        return 0;
    }
    for (int i=1; i<N; ++i) {
        cin >> a;
        while (num_child[stk.top()] == 0) stk.pop();
        if (parent[a-1] != stk.top()) {
            cout << 0;
            return 0;
        }
        --num_child[stk.top()];
        stk.push(a-1);
    }

    cout << 1;

    return 0;
}