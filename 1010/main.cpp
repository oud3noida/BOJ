#include <iostream>
#include <vector>

using namespace std;

int tests, n, m;
vector<vector<int>> cache;
int combination(int a, int b) {
    if (a == 0) return 0;
    if (b == 0 || b == a) return 1;
    
    int &ret = cache[a][b];
    if (ret != -1) return ret;
    
    ret = combination(a-1, b-1) + combination(a-1, b);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    cache.assign(30, vector<int>(30, -1));
    
    for (int i = 0; i < tests; i++) {
        cin >> n >> m;
        cout << combination(m, n) << '\n';
    }
    
    return 0;
}
