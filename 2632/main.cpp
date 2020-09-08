#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int MAX = 1000001;
int S, m, n;
vector<int> A, B, sumA, sumB;
long long ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> S >> m >> n;
    
    A.assign(m, 0);
    B.assign(n, 0);
    for (int i=0; i<m; ++i) cin >> A[i];
    for (int i=0; i<n; ++i) cin >> B[i];
    
    sumA.assign(MAX, 0);
    sumB.assign(MAX, 0);
    for (int i=0; i<m; ++i) {
        int pSumA = A[i];
        sumA[pSumA] += 1;
        for (int j=(i+1)%m; j!=i; j=(j+1)%m) {
            pSumA += A[j];
            sumA[pSumA] += 1;
        }
        if (i>0) sumA[pSumA] -= 1;
    }
    for (int i=0; i<n; ++i) {
        int pSumB = B[i];
        sumB[pSumB] += 1;
        for (int j=(i+1)%n; j!=i; j=(j+1)%n) {
            pSumB += B[j];
            sumB[pSumB] += 1;
        }
        if (i>0) sumB[pSumB] -= 1;
    }
    
    ans = 0;
    if (S < MAX) ans += sumA[S] + sumB[S];
    for (int i=max(1, S-MAX+1); i<min(S, MAX); ++i) {
        ans += sumA[i] * sumB[S-i];
    }
    
    cout << ans;
    
    return 0;
}
