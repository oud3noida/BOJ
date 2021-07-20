#include <iostream>
#include <map>

using namespace std;

const long long MOD = 1'000'000'007;
map<long long, long long> cache;

// F_(2n-1) = (F_(n-1))^2 + (F_n)^2
// F_2n = (2*F_(n-1) + F_n) * F_n
long long fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;
    
    if (cache.find(n) != cache.end()) return cache[n];
    
    if (n%2 == 0) {
        long long a1 = fibonacci(n/2-1);
        long long a2 = fibonacci(n/2);
        cache[n] = ((2LL*a1 + a2) * a2) % MOD;
    } else {
        long long b1 = fibonacci((n+1)/2-1);
        long long b2 = fibonacci((n+1)/2);
        cache[n] = (b1*b1 + b2*b2) % MOD;
    }
    return cache[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    cin >> n;
    cout << fibonacci(n);
    
    return 0;
}
