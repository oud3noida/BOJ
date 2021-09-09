#include <iostream>
#include <vector>

using namespace std;

struct Fenwick_Tree {
    vector<int> data;
    
    Fenwick_Tree(int n) {
        data.assign(n+1, 0);
    }
    
    int range_sum(int left, int right) {
        if (left != 1) return range_sum(1, right) - range_sum(1, left - 1);
        
        int ret = 0;
        while (right != 0) {
            ret += data[right];
            right &= (right - 1);
        }
        
        return ret;
    }
    
    void update(int index, int increment) {
        while (index <= data.size()) {
            data[index] += increment;
            index += index & ~(index - 1);
        }
    }
};

int n, top, ans;
vector<int> index;
Fenwick_Tree* tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    tree = new Fenwick_Tree(n);
    index.assign(n, -1);
    top = 1;
    
    ans = 0;
    int x;
    for (int i = 0; i < 2*n; i++) {
        cin >> x;
        if (index[x-1] == -1) {
            index[x-1] = top++;
            tree->update(index[x-1], 1);
        } else {
            tree->update(index[x-1], -1);
            ans += tree->range_sum(index[x-1] + 1, n);
        }
    }
    
    cout << ans;
    
    return 0;
}
