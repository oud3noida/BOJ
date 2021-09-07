#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> cows, num_moves;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    cows.assign(n, 0);
    num_moves.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    
    int i = 0;
    int cnt = 0;
    while (cnt <= n) {
        if (cows[i] == 0) {
            int i_prev = (i - 1 + n) % n;
            
            if (cows[i_prev] == 0) {
                i = (i + 1) % n;
                continue;
            }
            
            --cows[i_prev];
            ++cows[i];
            
            num_moves[i] = num_moves[i_prev] + 1;
            num_moves[i_prev] = 0;
            
            cnt = -1;
        }
        
        i = (i + 1) % n;
        ++cnt;
    }
    
    int ans = 0;
    for (int d : num_moves) {
        ans += d*d;
    }
    
    cout << ans;
    
    return 0;
}
