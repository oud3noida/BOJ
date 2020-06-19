#include <iostream>

using namespace std;

const int MAX = 100000;
const long long LOWER_BOUND = -123456789012345;
int n, minPSumIdx, maxPSumIdx;
int funIndex[MAX],
    pSumLeft[MAX], pSumRight[MAX],
    minSumBefore[MAX], minSumAfter[MAX],
    maxSumBefore[MAX], maxSumAfter[MAX];

int max(int x, int y, int z) {
    return max(max(x, y), z);
}

int min(int x, int y, int z) {
    return min(min(x, y), z);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) cin >> funIndex[i];
    
    // Calculate partial sum
    pSumLeft[0] = funIndex[0];
    pSumRight[n-1] = funIndex[n-1];
    for (int i=1; i<n; i++) pSumLeft[i] = pSumLeft[i-1] + funIndex[i];
    for (int i=n-2; i>=0; i--) pSumRight[i] = pSumRight[i+1] + funIndex[i];
    
    // Calculate min&max subarray sum of funIndex[0...i+1]
    minSumBefore[0] = maxSumBefore[0] = funIndex[0];
    minPSumIdx = maxPSumIdx = 0;
    for (int i=1; i<n; i++) {
        minSumBefore[i] = min(pSumLeft[i], pSumLeft[i]-pSumLeft[maxPSumIdx], minSumBefore[i-1]);
        maxSumBefore[i] = max(pSumLeft[i], pSumLeft[i]-pSumLeft[minPSumIdx], maxSumBefore[i-1]);
        
        if (pSumLeft[i] < pSumLeft[minPSumIdx]) minPSumIdx = i;
        if (pSumLeft[i] > pSumLeft[maxPSumIdx]) maxPSumIdx = i;
    }
    
    // Calculate min&max subarray sum of funIndex[i...n]
    minSumAfter[n-1] = maxSumAfter[n-1] = funIndex[n-1];
    minPSumIdx = maxPSumIdx = n-1;
    for (int i=n-2; i>=0; i--) {
        minSumAfter[i] = min(pSumRight[i], pSumRight[i]-pSumRight[maxPSumIdx], minSumAfter[i+1]);
        maxSumAfter[i] = max(pSumRight[i], pSumRight[i]-pSumRight[minPSumIdx], maxSumAfter[i+1]);
        
        if (pSumRight[i] < pSumRight[minPSumIdx]) minPSumIdx = i;
        if (pSumRight[i] > pSumRight[maxPSumIdx]) maxPSumIdx = i;
    }
    
    // Calculate the max value among the product of min/max subarray sums
    long long ans = LOWER_BOUND;
    for (int i=0; i<n-1; i++) {
        ans = max(ans, (long long) minSumBefore[i] * (long long) minSumAfter[i+1]);
        ans = max(ans, (long long) minSumBefore[i] * (long long) maxSumAfter[i+1]);
        ans = max(ans, (long long) maxSumBefore[i] * (long long) minSumAfter[i+1]);
        ans = max(ans, (long long) maxSumBefore[i] * (long long) maxSumAfter[i+1]);
    }
    
    cout << ans;
    
    return 0;
}
