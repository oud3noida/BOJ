#include <iostream>
#include <vector>

using namespace std;

int len;
string N;
vector<int> numDigit;

int char2num(char c) {
    return c - '0';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    len = N.length();
    numDigit.assign(10, 0);
    
    for (int i=0; i<len; ++i) ++numDigit[char2num(N[i])];
    
    if (numDigit[0] + numDigit[1] + numDigit[2] + numDigit[8] == len) {
        if (numDigit[0] * numDigit[1] * numDigit[2] * numDigit[8] != 0) {
            if (numDigit[0] == numDigit[1] && numDigit[1] == numDigit[2] && numDigit[2] == numDigit[8])
                cout << 8;
            else cout << 2;
        } else cout << 1;
    } else cout << 0;
    
    return 0;
}
