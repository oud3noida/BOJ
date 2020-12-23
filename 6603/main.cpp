#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n != 0) {
        vector<int> numbers(n, 0), permutation(n, 0);
        for (int i=0; i<n; ++i) cin >> numbers[i];
        for (int i=MAX; i<n; ++i) permutation[i] = 1;

        while (true) {
            for (int i=0; i<n; ++i)
                if (permutation[i] == 0) cout << numbers[i] << " ";
            if (next_permutation(permutation.begin(), permutation.end()))
                cout << "\n";
            else break;
        }

        cin >> n;
        if (n != 0) cout << "\n\n";
    }

    return 0;
}