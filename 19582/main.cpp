#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> limit, price;

bool solve(int cur, long long money, bool passed, int maxPrice) {
    if (cur == N) return true;
    
    if (cur > 0) maxPrice = max(maxPrice, price[cur-1]);
    if (money > limit[cur]) {
        if (passed) return false;
        
        if (money - maxPrice > limit[cur])
            return solve(cur+1, money, true, maxPrice);
        else
            return solve(cur+1, money - maxPrice + price[cur], true, maxPrice)
                || solve(cur+1, money, true, maxPrice);
    }
    return solve(cur+1, money + price[cur], passed, maxPrice);
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
    
    cout << (solve(0, 0, false, 0) ? "Kkeo-eok" : "Zzz");
    
    return 0;
}
