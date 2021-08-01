#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX = 60;
constexpr long long MOD = 1'000'000'007;
long long a, x;
vector<long long> powers;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> a >> x;
    
    powers.assign(MAX, 1);
    powers[0] = a % MOD;
    for (int i=1; i<MAX; ++i) {
        powers[i] = (powers[i-1] * powers[i-1]) % MOD;
    }
    
    long long a_power_x = 1;
    int i = MAX-1;
    while (i >= 0) {
        if (x - (1LL<<i) >= 0) {
            a_power_x = (a_power_x * powers[i]) % MOD;
            x -= (1LL<<i);
        }
        --i;
    }
    
    cout << a_power_x;
    
    return 0;
}
