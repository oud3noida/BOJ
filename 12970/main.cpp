#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int length, ab;
    cin >> length >> ab;

    for (int num_b = 1; num_b <= length/2; ++num_b) {
        int max_ab = num_b * (length - num_b);
        if (ab > max_ab) continue;
        int border = length - num_b;
        for (int i=0; i<length; ++i) {
            if (i > border || i == border - (max_ab - ab)) cout << 'B';
            else cout << 'A';
        }
        return 0;
    }

    cout << -1;
    return 0;
}