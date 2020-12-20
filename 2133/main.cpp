#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n%2 != 0) {cout << 0; return 0;}
    n /= 2;

    vector<int> ways(n, 2);
    ways[0] = 3;

    for (int i=0; i<n; ++i) {
        for (int j=0; j<i; ++j) {
            if (j == i-1) ways[i] += ways[j] * 3;
            else ways[i] += ways[j] * 2;
        }
    }

    cout << ways[n-1];

    return 0;
}