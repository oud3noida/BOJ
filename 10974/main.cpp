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
    for (int i = 0; i < n; ++i) permutation[i] = i+1;
    while (true) {
        for (int i = 0; i < n; ++i) cout << permutation[i] << " ";
        if (next_permutation(permutation.begin(), permutation.end())) {
            cout << "\n";
        } else break;
    }

    return 0;
}