#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 15746;
int n;
vector<int> fibonacci;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    fibonacci.assign(n+1, 1);
    for (int i = 2; i <= n; i++) {
        fibonacci[i] = (fibonacci[i-2] + fibonacci[i-1]) % MOD;
    }
    
    cout << fibonacci[n];

    return 0;
}
