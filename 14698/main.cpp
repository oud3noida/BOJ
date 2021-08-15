#include <iostream>
#include <queue>

using namespace std;

constexpr long long MOD = 1'000'000'007;
int tests, n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    
    for (int t = 0; t < tests; ++t) {
        cin >> n;
        
        long long e;
        priority_queue<long long, vector<long long>, greater<long long>> slime_energy;
        for (int i = 0; i < n; ++i) {
            cin >> e;
            slime_energy.push(e);
        }
        
        long long ans = 1;
        while (slime_energy.size() > 1) {
            long long slime1 = slime_energy.top();
            slime_energy.pop();
            long long slime2 = slime_energy.top();
            slime_energy.pop();
            
            cout << slime1 << ' ' << slime2 << ' ' << slime1*slime2 << endl;
            
            long long merged_slime = slime1 * slime2;
            slime_energy.push(merged_slime);
            
            merged_slime %= MOD;
            ans *= merged_slime;
            ans %= MOD;
        }
        
        cout << ans << '\n';
    }

    return 0;
}
