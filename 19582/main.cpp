#include <iostream>
#include <vector>

using namespace std;

int N, maxPrice;
vector<int> limit, price;

bool solve(int cur, long long money, bool passed) {
    if (cur == N) return true;
    
    if (cur > 0) maxPrice = max(maxPrice, price[cur-1]);
    if (money > limit[cur]) {
        if (passed) return false;
        if (money - maxPrice > limit[cur])
            return solve(cur+1, money, true);
        else
            return solve(cur+1, money - maxPrice + price[cur], true)
                || solve(cur+1, money, true);
    }
    return solve(cur+1, money + price[cur], passed);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    int x;
    for (int i=0; i<N; ++i) {
        cin >> x;
        limit.push_back(x);
        cin >> x;
        price.push_back(x);
    }
    maxPrice = 0;
    
    cout << (solve(0, 0, false) ? "Kkeo-eok" : "Zzz");
    
    return 0;
}
