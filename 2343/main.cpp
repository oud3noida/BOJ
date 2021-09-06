#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> lessons, p_sum;

bool is_possible(int gap) {
    auto last = p_sum.begin();
    for (int i = 0; i < m; i++) {
        last = prev(upper_bound(p_sum.begin(), p_sum.end(), *last + gap));
    }
    
    return last >= prev(p_sum.end());
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    
    lessons.assign(n, 0);
    p_sum.assign(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> lessons[i];
        p_sum[i + 1] = p_sum[i] + lessons[i];
    }
    
    int left = 1;
    int right = p_sum.back();
    while (left < right) {
        int mid = (left + right) / 2;
        if (is_possible(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    cout << left;
    
    return 0;
}
