#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> side, cache;

int crossroads(int left, int right) {
    if (left == n || right == n) return 0;
    
    int &ret = cache[left][right];
    if (ret != -1) return ret;
    
    ret = 0;
    if (abs(side[0][left] - side[1][right]) <= 4) {
        ret = max(ret, crossroads(left + 1, right + 1) + 1);
    }
    ret = max(ret, crossroads(left + 1, right));
    ret = max(ret, crossroads(left, right + 1));
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    side.assign(2, vector<int>(n, 0));
    for (int s = 0; s < 2; ++s) {
        for (int i = 0; i < n; i++) {
            cin >> side[s][i];
        }
    }
    
    cache.assign(n, vector<int>(n, -1));
    cout << crossroads(0, 0);
    
    return 0;
}
