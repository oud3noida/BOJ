#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> cows;
vector<int> cow_y;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        cows.emplace_back(x, y);
        cow_y.push_back(y);
    }
    
    sort(cows.begin(), cows.end());
    sort(cow_y.begin(), cow_y.end());
    
    int ans = n;
    
    int b = 0;
    int i = 0;
    while (i <= n) {
        vector<int> num_cows_in_region(4, 0);
        num_cows_in_region[0] = n - i;
        num_cows_in_region[3] = i;
        
        int a = 0;
        int j = 0;
        while (j <= n) {
            int max_cows = 0;
            for (int r = 0; r < 4; r++) {
                max_cows = max(max_cows, num_cows_in_region[r]);
            }
            ans = min(ans, max_cows);
            
            if (j < n) {
                do {
                    a = cows[j].first + 1;
                    
                    if (cows[j].second > b) {
                        num_cows_in_region[0]--;
                        num_cows_in_region[1]++;
                    } else {
                        num_cows_in_region[3]--;
                        num_cows_in_region[2]++;
                    }
                    
                    ++j;
                } while (j < n && a == cows[j].first + 1);
            } else {
                ++j;
            }
        }
        
        if (i < n) {
            do {
                b = cow_y[i] + 1;
                ++i;
            } while (i < n && b == cow_y[i] + 1);
        } else {
            ++i;
        }
    }
    
    cout << ans;
    
    return 0;
}
