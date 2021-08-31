#include <iostream>
#include <vector>

using namespace std;

constexpr int INF = 1'999'999'999;
int tests, n;
vector<int> arr, p_sum;
vector<vector<int>> cache;

int merge_file(int left, int right) {
    if (left == right) return 0;
    if (left + 1 == right) return arr[left] + arr[right];
    
    int &ret = cache[left][right];
    if (ret != INF) return ret;
    
    int sum_all = p_sum[right + 1] - p_sum[left];
    for (int mid = left; mid < right; mid++) {
        int cost = merge_file(left, mid) + merge_file(mid + 1, right);
        ret = min(ret, cost + sum_all);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    
    for (int t = 0; t < tests; t++) {
        cin >> n;
        
        arr.assign(n, 0);
        p_sum.assign(n+1, 0);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            p_sum[i+1] = p_sum[i] + arr[i];
        }
        
        cache.assign(n, vector<int>(n, INF));
        cout << merge_file(0, n-1) << '\n';
    }
    
    return 0;
}
