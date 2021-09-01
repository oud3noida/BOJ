#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX = 200;
constexpr int COMBINATION_MAX = 1'000'000'000;
vector<vector<int>> cache;
int a, z, k;

int combination(int n, int r) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (r == 0 || r == n) return 1;
    
    int &ret = cache[n][r];
    if (ret != -1) return ret;
    
    ret = min(combination(n-1, r-1) + combination(n-1, r), COMBINATION_MAX + 1);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cache.assign(MAX+1, vector<int>(MAX+1, -1));
    
    cin >> a >> z >> k;
    
    if (k > combination(a + z, z)) {
        cout << -1;
        return 0;
    }
    
    int index = 0;
    vector<char> ans(a + z, 'a');
    int z_position = a + z;
    
    for (int choose = z-1; choose > 0; --choose) {
        for (int from = choose; from < z_position; ++from) {
            if (index + combination(from, choose) >= k) {
                z_position = from;
                ans[z_position] = 'z';
                break;
            }
            
            index += combination(from, choose);
        }
    }
    
    ans[k - index - 1] = 'z';
    
    for (auto c = ans.rbegin(); c != ans.rend(); ++c) {
        cout << *c;
    }
    
    return 0;
}
