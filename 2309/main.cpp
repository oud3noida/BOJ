#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> candidates(9, 0), ans;
    for (int i=0; i<9; ++i) cin >> candidates[i];

    for (int a=0; a<9; ++a) {
        for (int b=a+1; b<9; ++b) {
            int sum_height = 0;
            ans.clear();
            for (int i=0; i<9; ++i) {
                if (i == a || i == b) continue;
                ans.push_back(candidates[i]);
                sum_height += candidates[i];
            }
            if (sum_height == 100) {
                sort(ans.begin(), ans.end());
                for (int h : ans) cout << h << "\n";
                return 0;
            }
        }
    }

    return 0;
}