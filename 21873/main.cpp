#include <iostream>

using namespace std;

int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int color = 1;
    cout << n*n + 2*n << '\n';
    
    int k = 1;
    bool increase = true;
    while (k > 0) {
        int begin = increase ? 1 : n - min(k, n) + 1,
            end = increase ? min(k, n) : n;
        
        for (int i=begin; i<=end; ++i) {
            cout << color << ' ' << i << '\n';
        }
        
        if (k > n) increase = false;
        
        k += increase ? 1 : -1;
        color = (color == 1) ? 2 : 1;
    }
    
    return 0;
}
