#include <iostream>
#include <cmath>

using namespace std;

string number;
int base, decimal;

int char2int(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    return c - '0';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> number >> base;
    
    decimal = 0;
    
    for (int i=0; i<number.length(); ++i) {
        char digit = number[number.length()-1-i];
        decimal += char2int(digit) * pow(base, i);
    }
    
    cout << decimal;
    
    return 0;
}
