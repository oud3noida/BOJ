#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, ans;
int isPrime[100001];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    fill(isPrime, isPrime+(n+1), true);
    for (int i=2; i<=sqrt(n); ++i) {
        if (!isPrime[i]) continue;
        
        for (int j=i*i; j<=n; j+=i) {
            isPrime[j] = false;
        }
        
        if (!isPrime[n]) break;
    }
    
    if (isPrime[n]) cout << "Yes";
    else cout << "No";
    
    return 0;
}
