#include <iostream>

using namespace std;

typedef long long bigInt;

bigInt n;
double ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    ans = n;
    for (bigInt i=2; i*i <= n; ++i) {
        if (n % i != 0) continue;
        
        while (n % i == 0) n /= i;
        
        ans *= (1.0 - 1.0 / (double) i);
    }
    if (n != 1) ans *= (1.0 - 1.0 / (double) n);
    
    cout << (bigInt) ans;
    
    return 0;
}
