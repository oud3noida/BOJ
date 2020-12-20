#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int data;
    vector<int> child;
    
    TreeNode(int x) : data(x) {}
    
    void addChild(int c) {
        child.push_back(c);
    }
    
    int numChild() {
        return child.size();
    }
};

int diameter;

int dfs(vector<TreeNode*> &tree, int cur) {
    int dst[2] = {0, 0};
    TreeNode *curNode = tree[cur];
    int curNumChild = curNode->numChild();
    for (int chi=0; chi<curNumChild; chi++) {
        int c = dfs(tree, curNode->child[chi]);
        if (c > dst[0]) {
            dst[1] = dst[0];
            dst[0] = c;
        } else if (c > dst[1]) dst[1] = c;
    }
    diameter = max(diameter, dst[0]+dst[1]);
    return max(dst[0], dst[1]) + curNode->data;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    diameter = 0;
    cin >> n;
    
    vector<TreeNode*> tree(n, new TreeNode(0));
    for (int i=0; i<n-1; i++) {
        int par, chi, d;
        cin >> par >> chi >> d;
        tree[chi-1] = new TreeNode(d);
        tree[par-1]->addChild(chi-1);
    }
    
    dfs(tree, 0);
    
    cout << diameter;

    return 0;
}
