#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> arr(n, 0);
    for (int i=0; i<n; ++i) cin >> arr[i];

    int ans = 0;
    vector<int> sum(1<<n, 0);

    int i = 0;
    for (int bit_index = 1; bit_index < 1<<n; ++bit_index) {
       if (bit_index >= (1<<(i+1))) ++i;
       sum[bit_index] = sum[bit_index & ((1<<i)-1)] + arr[i];
       if (sum[bit_index] == target) ++ans;
    }

    cout << ans;

    return 0;
}