#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 1'000'001;
int n;
vector<pair<int, int>> sequence;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int x;
    for (int i=0; i<n; ++i) {
        cin >> x;
        sequence.emplace_back(x, i);
    }
    
    stable_sort(sequence.begin(), sequence.end());
    
    int ans = 0;
    for (int i=0; i<n; ++i) {
        ans = max(ans, sequence[i].second - i + 1);
    }
    
    cout << ans;
    
    return 0;
}
