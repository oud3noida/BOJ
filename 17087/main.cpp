#include <iostream>

using namespace std;

int n, start, all_gcd;

int gcd(int a, int b) {
    if (a%b == 0) return b;
    return gcd(b, a%b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> start >> all_gcd;
    all_gcd = abs(all_gcd - start);
    
    int a;
    for (int i=1; i<n; ++i) {
        cin >> a;
        all_gcd = gcd(all_gcd, abs(a-start));
    }
    
    cout << all_gcd;
    
    return 0;
}
