#include <iostream>

using namespace std;

const int N = 1000;
int n, maxLen, ans;
int arr[N], forwardLen[N], backwardLen[N];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) cin >> arr[i];
    
    for (int i=0; i<n; i++) {
        maxLen = 0;
        
        for (int j=0; j<i; j++) 
            if (arr[j] < arr[i]) maxLen = max(maxLen, forwardLen[j]);
        
        forwardLen[i] = maxLen + 1;
    }
    
    for (int i=n-1; i>=0; i--) {
        maxLen = 0;
        
        for (int j=n-1; i<j; j--) 
            if (arr[i] > arr[j]) maxLen = max(maxLen, backwardLen[j]);
        
        backwardLen[i] = maxLen + 1;
    }
    
    int ans = 0;
    for (int i=0; i<n; i++)
        ans = max(ans, forwardLen[i] + backwardLen[i] - 1);
    
    cout << ans;
    
    return 0;
}
