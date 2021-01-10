#include <iostream>
#include <vector>

using namespace std;

int N, root, traversal_idx, max_depth;
vector<int> parent, depth, min_column_memo, max_column_memo;
vector<pair<int, int>> child;

void inorder_traversal(int cur, int cur_depth) {
    int left_child = child[cur].first,
        right_child = child[cur].second;

    if (left_child != -1) inorder_traversal(left_child, cur_depth + 1);
    depth[traversal_idx++] = cur_depth;
    if (right_child != -1) inorder_traversal(right_child, cur_depth + 1);

    max_depth = max(max_depth, cur_depth);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    parent.assign(N+1, -1);
    child.assign(N+1, make_pair(-1, -1));

    int par, left_child, right_child;
    for (int i=1; i<=N; ++i) {
        cin >> par >> left_child >> right_child;
        child[par] = make_pair(left_child, right_child);
        if (left_child != -1) parent[left_child] = par;
        if (right_child != -1) parent[right_child] = par;
    }

    for (int i=1; i<=N; ++i) {
        if (parent[i] != -1) continue;
        root = i;
        break;
    }

    depth.assign(N, -1);
    traversal_idx = 0;
    max_depth = 1;
    inorder_traversal(root, 1);

    min_column_memo.assign(max_depth + 1, N+1);
    max_column_memo.assign(max_depth + 1, -1);
    for (int i=0; i<N; ++i) {
        min_column_memo[depth[i]] = min(min_column_memo[depth[i]], i);
        max_column_memo[depth[i]] = max(max_column_memo[depth[i]], i);
    }

    int ans_width = -1, ans_depth = 1;
    for (int d=1; d<=max_depth; ++d) {
        int cur_width = max_column_memo[d] - min_column_memo[d] + 1;
        if (ans_width < cur_width) {
            ans_width = cur_width;
            ans_depth = d;
        }
    }

    cout << ans_depth << ' ' << ans_width;

    return 0;
}