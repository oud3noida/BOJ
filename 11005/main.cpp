#include <iostream>
#include <cmath>

using namespace std;

int decimal, base;

char int2char(int n) {
    if (n < 10) return n + '0';
    return (n-10) + 'A';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> decimal >> base;
    
    if (decimal == 0) {
        cout << 0;
        return 0;
    }
    
    int x = 0;
    while (pow(base, x) <= decimal) ++x;
    --x;
        
    for (; x>=0; --x) {
        int base_power_x = pow(base, x);
        cout << int2char(decimal / base_power_x);
        decimal %= base_power_x;
    }
    
    return 0;
}
