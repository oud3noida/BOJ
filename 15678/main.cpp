#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr long long UNDEFINED = numeric_limits<long long>::min();
int n, d;
vector<long long> stones, cache;

int lsb(int x) {
    return x & ~(x-1);
}

class Fenwick_Tree {
    private:
    int tree_type, size;
    vector<long long> data;
    
    public: Fenwick_Tree(int type, int size):
        tree_type(type), size(size) {
        data.assign(size+1, UNDEFINED);
    }
    
    public: long long at(int i) const {
        return data[i];
    }
    
    private: bool in_range(int i) const {
        return 1 <= i && i <= size;
    }
    
    public: int parent(int i) const {
        return tree_type == 1 ? i + lsb(i) : i - lsb(i);
    }
    
    private: vector<int> children(int i) const {
        vector<int> ret;
        
        int increment = tree_type == 1 ? -1 : 1;
        int child = i + increment;
        while (parent(child) == i) {
            ret.push_back(child);
            child += lsb(child) * increment;
        }
        
        return ret;
    }
    
    public: void update(int i, long long new_value) {
        long long old_value = data[i];
        
        while (in_range(i)) {
            if (new_value < data[i]) {
                if (old_value < data[i]) return;
                
                new_value = max(new_value, cache[i]);
                for (int child : children(i)) {
                    new_value = max(new_value, data[child]);
                }
            }
            
            if (new_value == data[i]) return;
            
            data[i] = new_value;
            i = parent(i);
        }
    }
};

Fenwick_Tree *tree1, *tree2;

long long max_cache_range(int left, int right) {
    if (left > n) return 0;
    if (right > n) return max_cache_range(left, n);
    
    long long ret = UNDEFINED;
    int i;
    
    i = left;
    while (tree1->parent(i) <= right) {
        ret = max(ret, tree2->at(i));
        i = tree1->parent(i);
    }
    
    i = right;
    while (tree2->parent(i) >= left) {
        ret = max(ret, tree1->at(i));
        i = tree2->parent(i);
    }
    
    ret = max(ret, cache[i]);
    return ret;
}

void update_cache(int i, long long new_value) {
    tree1->update(i, new_value);
    tree2->update(i, new_value);
    cache[i] = new_value;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> d;
    
    stones.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> stones[i];
    }
    
    cache.assign(n+1, UNDEFINED);
    tree1 = new Fenwick_Tree(1, n);
    tree2 = new Fenwick_Tree(2, n);
    
    long long ans = UNDEFINED;
    for (int i = n; i >= 1; i--) {
        long long new_value = max(0LL, max_cache_range(i + 1, i + d)) + stones[i];
        update_cache(i, new_value);
        ans = max(ans, cache[i]);
    }
    
    cout << ans;
    
    return 0;
}
