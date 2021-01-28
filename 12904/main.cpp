#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string initial_string, changed_string;
    cin >> initial_string >> changed_string;

    int initial_length = initial_string.size(),
        forward_idx = 0,
        backward_idx = changed_string.size() - 1;
    bool reversed = false;
    while (backward_idx - forward_idx >= initial_length) {
        int &idx = reversed ? forward_idx : backward_idx,
            increment = reversed ? 1 : -1;
        if (changed_string[idx] == 'B') reversed = !reversed;
        idx += increment;
    }

    for (int i=0; i<=backward_idx - forward_idx; ++i) {
        int j = reversed ? backward_idx - i : forward_idx + i;
        if (initial_string[i] != changed_string[j]) {
            cout << 0;
            return 0;
        }
    }

    cout << 1;
    return 0;
}