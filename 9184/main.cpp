#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int UNDEFINED = numeric_limits<int>::min();
constexpr int MAX = 20;
vector<vector<vector<int>>> cache;

int w(int a, int b, int c) {
    /* 
     * if a <= 0 or b <= 0 or c <= 0, then w(a, b, c) returns:
     *     1
     * 
     * if a > 20 or b > 20 or c > 20, then w(a, b, c) returns:
     *     w(20, 20, 20)
     * 
     * if a < b and b < c, then w(a, b, c) returns:
     *     w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)
     * 
     * otherwise it returns:
     *     w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)
     */
    
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    
    if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
    
    int &ret = cache[a][b][c];
    if (ret != UNDEFINED) return ret;
    
    if (a < b && b < c) {
        ret = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
    } else {
        ret = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
    }
    
    return ret;
}

int a, b, c;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cache.assign(MAX+1, vector<vector<int>>(MAX+1, vector<int>(MAX+1, UNDEFINED)));
    
    while (true) {
        cin >> a >> b >> c;
        
        if (a == -1 && b == -1 && c == -1) break;
        
        cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << '\n';
    }

    return 0;
}
