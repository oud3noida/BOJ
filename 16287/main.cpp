#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, w;
vector<int> arr;
vector<bool> twoSum;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
        
    cin >> w >> n;
    
    arr.assign(n, 0);
    for (int i=0; i<n; ++i) cin >> arr[i];
    
    twoSum.assign(w+1, false);
    
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            if (arr[i] + arr[j] >= w) continue;
            if (twoSum[w - arr[i] - arr[j]]) {
                cout << "YES";
                return 0;
            }
        }
                
        for (int j=0; j<i; ++j) {
            if (arr[i] + arr[j] >= w) continue;
            twoSum[arr[i] + arr[j]] = true;
        }
    }
    
    cout << "NO";
    return 0;
}