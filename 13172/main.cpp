#include <iostream>

using namespace std;

const long long MOD = 1'000'000'007; 
int n;
long long a, b;

long long x_inverse(long long x, long long mod) {
    long long r0 = x, r1 = mod,
              s0 = 1, s1 = 0,
              t0 = 0, t1 = 1,
              tmp = 0, q = 0;
    
    while (r1 != 0) {
        q = r0 / r1;
        
        tmp = r0 - r1*q;
        r0 = r1;
        r1 = tmp;
        
        tmp = s0 - s1*q;
        s0 = s1;
        s1 = tmp;
        
        tmp = t0 - t1*q;
        t0 = t1;
        t1 = tmp;
    }
    
    return s0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    long long answer = 0;
    for (int i=0; i<n; ++i) {
        cin >> b >> a;
        long long b_inverse = x_inverse(b, MOD);
        answer += a*b_inverse % MOD;
        answer %= MOD;
    }
    
    cout << (answer+MOD) % MOD;
    
    return 0;
}
