#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_hays, num_cows;
vector<int> hays;

bool is_detonatable(int r) {
    auto hay = hays.begin();
    for (int i = 0; i < num_cows; i++) {
        hay = upper_bound(hays.begin(), hays.end(), *hay + r);
        if (hay == hays.end()) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_hays >> num_cows;
    
    hays.assign(num_hays, 0);
    for (int i = 0; i < num_hays; i++) {
        cin >> hays[i];
    }
    sort(hays.begin(), hays.end());
    
    int left = 1;
    int right = 1'000'000'000;
    while (left < right) {
        int mid = (left + right) / 2;
        if (is_detonatable(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    cout << (left + 1) / 2;
    
    return 0;
}
