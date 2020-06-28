#include <iostream>

using namespace std;

long long n, ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    ans = 0;
    for (int i=1; i<=n; ++i) {
        if (n % i) continue;
        ans += i;
    }
    
    cout << ans*5 - 24;
    
    return 0;
}
