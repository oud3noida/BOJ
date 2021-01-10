#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int char_to_num(char c) {
    return (int) (c - 'A');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int num_character = 0;
    vector<int> char_to_int_idx(26, -1);

    vector<string> words(N, "");
    for (int i=0; i<N; ++i) {
        cin >> words[i];
        for (char c : words[i]) {
            assert('A' <= c && c <= 'Z');
            if (char_to_int_idx[char_to_num(c)] != -1) continue;
            char_to_int_idx[char_to_num(c)] = num_character++;
        }
    }

    assert(0 < num_character && num_character <= 10);
    vector<int> mask(10, 0);
    for (int i=0; i<10; ++i) mask[i] = i;

    int ans = 0;
    do {
        int sum = 0;
        for (const string& word : words) {
            int cur_num = 0;
            for (char c : word) {
                cur_num *= 10;
                cur_num += mask[char_to_int_idx[char_to_num(c)]];
            }
            sum += cur_num;
        }
        ans = max(ans, sum);
    } while (next_permutation(mask.begin(), mask.end()));

    cout << ans;

    return 0;
}