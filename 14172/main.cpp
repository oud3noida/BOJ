#include <iostream>
#include <vector>

using namespace std;

struct Cow {
    int x, y, r;
    
    Cow(int x, int y, int r) : x(x), y(y), r(r) {}
    
    bool is_reachable(const Cow &other) const {
        return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y) <= r*r;
    }
};

int n;
vector<Cow> cows;
vector<vector<int>> children;
vector<bool> visited;

int num_descendants(int i) {
    if (visited[i]) return 0;
    visited[i] = true;
    
    int ret = 1;
    for (int child : children[i]) {
        ret += num_descendants(child);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int x, y, r;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> r;
        cows.emplace_back(x, y, r);
    }
    
    children.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (cows[i].is_reachable(cows[j])) {
                children[i].push_back(j);
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        visited.assign(n, false);
        ans = max(ans, num_descendants(i));
    }
    
    cout << ans;
    
    return 0;
}
