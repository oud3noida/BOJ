#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5000;
const long long INF = 3987654321;
int n;
long long minAbsSum;
long long arr[N+1];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) cin >> arr[i];
    arr[N] = INF;
    
    sort(arr, arr+n);
    
    minAbsSum = INF;
    long long ans[3];
    // Two-pointer approach & one pivot (from arr[0] to arr[n-3])
    for (int i=0; i<n-2; i++) {
        int a = i+1;
        int b = n-1;
        while (a < b) {
            if (abs(arr[a]+arr[b]+arr[i]) < minAbsSum) {
                minAbsSum = abs(arr[a]+arr[b]+arr[i]);
                ans[0] = arr[a]; ans[1] = arr[b]; ans[2] = arr[i];
            }
            
            if (arr[a]+arr[b]+arr[i] < 0) a++;
            else b--;
        }
    }
    
    // NOTE: Output must be in the ascending order
    sort(ans, ans+3);
    for (int i=0; i<3; i++) cout << ans[i] << " ";
    
    return 0;
}
