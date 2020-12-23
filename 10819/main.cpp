#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> numbers(n, 0), perm(n, 0);
    for (int i=0; i<n; ++i) cin >> numbers[i];
    for (int i=0; i<n; ++i) perm[i] = i;

    int max_sum_diff = 0;
    do {
        int sum_diff = 0;
        for (int i=1; i<n; ++i) sum_diff += abs(numbers[perm[i-1]] - numbers[perm[i]]);
        max_sum_diff = max(max_sum_diff, sum_diff);
    } while (next_permutation(perm.begin(), perm.end()));

    cout << max_sum_diff;

    return 0;
}