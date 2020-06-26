#include <iostream>
#include <string.h>

using namespace std;

const int MOD = 1000000000, MAX = 100;
int n, ans;
int cache[MAX][1<<10][10];

int stairNums(int i, int visited, int cur) {
    if (i == n-1) {
        if (visited == (1<<10)-1) return 1;
        else return 0;
    }
    
    int &ret = cache[i][visited][cur];
    if (ret != -1) return ret;
    
    ret = 0;
    
    if (cur > 0)
        ret += stairNums(i+1, visited|(1<<(cur-1)), cur-1) % MOD;
    ret %= MOD;
    
    if (cur < 9)
        ret += stairNums(i+1, visited|(1<<(cur+1)), cur+1) % MOD;
    ret %= MOD;
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    memset(cache, -1, sizeof(cache));
    
    ans = 0;
    for (int i=1; i<=9; i++) {
        ans += stairNums(0, 1<<i, i);
        ans %= MOD;
    }
    
    cout << ans;
    
    return 0;
}
