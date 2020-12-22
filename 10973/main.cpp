#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> permutation(n, 0);
    for (int i = 0; i < n; ++i) cin >> permutation[i];
    if (prev_permutation(permutation.begin(), permutation.end())) {
        for (int i = 0; i < n; ++i) cout << permutation[i] << " ";
    } else cout << -1;

    return 0;
}