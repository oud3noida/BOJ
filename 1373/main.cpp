#include <iostream>
#include <vector>

using namespace std;

string binary;
vector<int> octal;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> binary;
    
    for (int i=binary.length()-1; i>=0; i -= 3) {
        int octal_digit = 0;
        for (int j=0; j<=min(2, i); ++j) {
            if (binary[i-j] == '1'){
                octal_digit += 1<<j;
            }
        }
        octal.push_back(octal_digit);
    }
    
    for (auto o = octal.rbegin(); o != octal.rend(); ++o)
        cout << *o;
    
    return 0;
}
