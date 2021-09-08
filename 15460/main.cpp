#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr double EPSILON = 0.0001;
int n;
vector<int> scores, sum_from_behind, min_from_behind;
vector<pair<double, int>> final_score_and_k;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    scores.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
    }
    
    sum_from_behind.assign(n, scores[n-1]);
    min_from_behind.assign(n, scores[n-1]);
    for (int i = n-2; i >= 0; i--) {
        sum_from_behind[i] = sum_from_behind[i + 1] + scores[i];
        min_from_behind[i] = min(min_from_behind[i + 1], scores[i]);
    }
    
    for (int k = 1; k <= n-2; k++) {
        double final_score_sum = sum_from_behind[k] - min_from_behind[k];
        double final_score = final_score_sum / (n - k - 1);
        final_score_and_k.emplace_back(final_score, k);
    }
    sort(final_score_and_k.begin(), final_score_and_k.end());
    
    auto it = final_score_and_k.rbegin();
    double max_score = it->first;
    vector<int> ans;
    for (; max_score - it->first < EPSILON; ++it) {
        ans.push_back(it->second);
    }
    sort(ans.begin(), ans.end());
    
    for (int k : ans) {
        cout << k << '\n';
    }
    
    return 0;
}
