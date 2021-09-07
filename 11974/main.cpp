#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> cows, p_sum;
vector<pair<int, int>> mod_extremes;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    cows.assign(n, 0);
    p_sum.assign(n + 1, 0);
    mod_extremes.assign(7, make_pair(n, 0));
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
        p_sum[i + 1] = (p_sum[i] + cows[i]) % 7;
        
        mod_extremes[p_sum[i + 1]].first = min(mod_extremes[p_sum[i + 1]].first, i + 1);
        mod_extremes[p_sum[i + 1]].second = max(mod_extremes[p_sum[i + 1]].second, i + 1);
    }
    mod_extremes[0].first = 0;
    
    int ans = 0;
    for (int i = 0; i < 7; i++) {
        ans = max(ans, mod_extremes[i].second - mod_extremes[i].first);
    }
    cout << ans;
    
    return 0;
}
