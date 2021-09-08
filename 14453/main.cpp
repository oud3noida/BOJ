#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n;
vector<vector<int>> p_sum;

int gesture_to_int(char c) {
    switch (c) {
        case 'H': return 0;
        case 'P': return 1;
        case 'S': return 2;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    p_sum.assign(3, vector<int>(n+1, 0));
    char c;
    for (int i = 1; i <= n; i++) {
        cin >> c;
        ++p_sum[gesture_to_int(c)][i];
        for (int g = 0; g < 3; g++) {
            p_sum[g][i] += p_sum[g][i-1];
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int before = 0;
        int after = 0;
        for (int g = 0; g < 3; g++) {
            before = max(before, p_sum[g][i]);
            after = max(after, p_sum[g][n] - p_sum[g][i]);
        }
        
        ans = max(ans, before + after);
    }
    
    cout << ans;
    
    return 0;
}
