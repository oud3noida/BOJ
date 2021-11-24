#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> arr;

bool is_partitionable(int from, int num_partitions, int bound) {
    if (num_partitions == 0) return false;
    
    int cur_min = arr[from], cur_max = arr[from];
    for (int to = from + 1; to < n; to++) {
        cur_min = min(cur_min, arr[to]);
        cur_max = max(cur_max, arr[to]);
        if (cur_max - cur_min > bound) {
            return is_partitionable(to, num_partitions - 1, bound);
        }
    }
    
    return true;
}

int solve() {
    int arr_min = *min_element(arr.begin(), arr.end()),
        arr_max = *max_element(arr.begin(), arr.end()),
        left = 0, right = arr_max - arr_min;
    
    while (left < right) {
        int mid = (left + right) / 2;
        if (is_partitionable(0, m, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    arr.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << solve();
    
    return 0;
}
