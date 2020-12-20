#include <iostream>
#include <vector>

using namespace std;

const int NEG_INF = -1'000'000'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n, 0), p_sum_left(n + 1, 0), p_sum_right(n + 1, 0);

    for (int i = 0; i < n; ++i) cin >> arr[i];

    int ans = NEG_INF;
    for (int i = 0; i < n; ++i) {
        p_sum_left[i + 1] = max(0, p_sum_left[i]) + arr[i];
        p_sum_right[n - i - 1] = max(0, p_sum_right[n - i]) + arr[n-i-1];
        ans = max(ans, p_sum_left[i + 1]);
    }

    if (n > 1) {
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, p_sum_left[i-1] + p_sum_right[i]);
        }
    }

    cout << ans;

    return 0;
}