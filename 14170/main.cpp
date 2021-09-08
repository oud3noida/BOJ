#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, num_queries;
vector<int> haybales;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_queries;
    
    haybales.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> haybales[i];
    }
    sort(haybales.begin(), haybales.end());
    
    int left, right;
    for (int q = 0; q < num_queries; q++) {
        cin >> left >> right;
        auto left_hay = lower_bound(haybales.begin(), haybales.end(), left);
        auto right_hay = upper_bound(haybales.begin(), haybales.end(), right);
        cout << right_hay - left_hay << '\n';
    }
    
    return 0;
}
