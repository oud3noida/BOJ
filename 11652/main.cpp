#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<long long> arr;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    arr.assign(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    
    long long ans = 0;
    int num_ans = 0;
    for (auto it = arr.begin(); it != arr.end();) {
        auto it_next = upper_bound(it, arr.end(), *it);
        
        if (num_ans < it_next - it) {
            num_ans = it_next - it;
            ans = *it;
        }
        
        it = it_next;
    }
    
    cout << ans;
    
    return 0;
}
