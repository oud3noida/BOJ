#include <iostream>
#include <vector>

using namespace std;

int n;

bool is_blank(int x, int y) {
    for (int i=3; i<=n; i*=3) {
        if (x % 3 == 1 && y % 3 == 1) return true;
        x /= 3;
        y /= 3;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    for (int y=0; y<n; ++y) {
        for (int x=0; x<n; ++x) {
            cout << (is_blank(x, y) ? ' ' : '*');
        }
        cout << '\n';
    }
    
    return 0;
}
