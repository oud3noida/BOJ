#include <iostream>
#include <vector>

using namespace std;

constexpr long long NEG_MAX = 11453246122, // 101010...1010
                    POS_MAX = 5726623061;  // 10101...10101

long long decimal;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> decimal;
    
    if (decimal == 0) {
        cout << 0;
        return 0;
    }
    
    long long msb = 1;
    while (!(msb - (NEG_MAX&(abs(msb)-1)) <= decimal
           && decimal <= msb + (POS_MAX&(abs(msb)-1)))) {
        msb *= -2;
    }
    
    for (; msb != 0; msb /= -2) {
        if (msb - (NEG_MAX&(abs(msb)-1)) <= decimal
            && decimal <= msb + (POS_MAX&(abs(msb)-1))) {
            cout << 1;
            decimal -= msb;
        } else {
            cout << 0;
        }
    }
    
    return 0;
}
