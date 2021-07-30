#include <iostream>
#include <cmath>

using namespace std;

int base_from, base_to, num_digits, decimal;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> base_from >> base_to >> num_digits;
    
    decimal = 0;
    
    int digit;
    for (int i=num_digits-1; i>=0; --i) {
        cin >> digit;
        decimal += digit * pow(base_from, i);
    }
    
    int x = 0;
    while (pow(base_to, x) <= decimal) ++x;
    --x;
        
    for (; x>=0; --x) {
        int base_power_x = pow(base_to, x);
        cout << decimal / base_power_x << ' ';
        decimal %= base_power_x;
    }
    
    return 0;
}
