#include <iostream>
#include <vector>

using namespace std;

int n, target, ans;
vector<int> partial_sum;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> target;
    
    int x;
    partial_sum.assign(n+1, 0);
    for (int i=0; i<n; ++i) {
        cin >> x;
        partial_sum[i+1] = partial_sum[i] + x;
    }
    
    ans = 0;
    for (int i=1; i<=n; ++i) {
        for (int j=i; j<=n; ++j) {
            if (partial_sum[j] - partial_sum[i-1] == target) ++ans;
        }
    }
    
    cout << ans;
    
    return 0;
}
