#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

struct TreeNode {
    int id, parent, left, right;
    TreeNode(int i=0, int p=-1) : id(i), parent(p), left(-1), right(-1) {}
};

int N, root;
ll query;
vector<TreeNode*> tree;

int solve(int cur, ll k) {
    int leftChild = tree[cur]->left,
        rightChild = tree[cur]->right;
    
    if (leftChild == -1 && rightChild == -1)
        return cur;
    if (leftChild == -1)
        return solve(rightChild, k);
    if (rightChild == -1)
        return solve(leftChild, k);
    
    if (k % 2 == 1)
        return solve(leftChild, k/2+1);
    else
        return solve(rightChild, k/2);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    tree.assign(N, NULL);
    for (int i=0; i<N; ++i) tree[i] = new TreeNode(i);
    
    int lc, rc;
    for (int i=0; i<N; ++i) {
        cin >> lc >> rc;
        if (lc != -1) {
            tree[i]->left = lc-1;
            tree[lc-1]->parent = i;
        }
        if (rc != -1) {
            tree[i]->right = rc-1;
            tree[rc-1]->parent = i;
        }
    }
    
    cin >> query;
    cout << solve(root, query)+1;
    
    return 0;
}
