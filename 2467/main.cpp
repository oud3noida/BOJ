#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 2123456789;
int n;
int minAbsSum;
int arr[100000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) cin >> arr[i];
    
    minAbsSum = INF;
    int ans[2];
    
    int a = 0, b = n-1;
    // Two-pointer apporach
    while (a < b) {
        if (abs(arr[a]+arr[b]) < minAbsSum) {
            minAbsSum = abs(arr[a]+arr[b]);
            ans[0] = arr[a]; ans[1] = arr[b];
        }
        if (arr[a]+arr[b] < 0) a++;
        else b--;
    }
    
    // NOTE: Output must be in the ascending order
    sort(ans, ans+2);
    for (int i=0; i<2; i++) cout << ans[i] << " ";
    
    return 0;
}
