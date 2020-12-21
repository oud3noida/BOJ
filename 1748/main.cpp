#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int i = 1, j = 9, ans = 0, n;
    cin >> n;

    while (n - j > 0) {
        n -= j;
        ans += i * j;
        i += 1;
        j *= 10;
    }

    cout << ans + i*n;

    return 0;
}