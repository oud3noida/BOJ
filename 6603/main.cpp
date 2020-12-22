#include <iostream>
#include <vector>

using namespace std;

int n;
const int MAX = 6;
vector<int> permutation, numbers;

void loop_permutation(int start, int depth) {
    if (depth >= MAX) {
        for (int i=0; i<MAX; ++i) cout << permutation[i] << " ";
        return;
    }
    for (int i=start; i<=n-MAX+depth; ++i) {
        permutation[depth] = numbers[i];
        loop_permutation(i+1, depth+1);
        if (i < n-MAX+depth) cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    permutation.assign(6, 0);

    cin >> n;
    while (n != 0) {
        numbers.assign(n, 0);
        for (int i=0; i<n; ++i) cin >> numbers[i];

        loop_permutation(0, 0);

        cin >> n;
        if (n != 0) cout << "\n\n";
    }

    return 0;
}