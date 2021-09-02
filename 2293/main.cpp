#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_coins, target_money;
vector<int> coins, cache;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_coins >> target_money;
    
    coins.assign(num_coins, 0);
    cache.assign(target_money+1, 0);
    for (int i = 0; i < num_coins; i++) {
        cin >> coins[i];
    }
    sort(coins.begin(), coins.end());
    
    int ans = 0;
    for (int i = 0; i < num_coins; i++) {
        int coin = coins[i];
        if (coin <= target_money) {
            ++cache[coin];
        }
        for (int money = coin; money <= target_money; ++money) {
            cache[money] += cache[money - coin];
        }
    }
    
    cout << cache[target_money];

    return 0;
}
