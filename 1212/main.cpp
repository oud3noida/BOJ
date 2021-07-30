#include <iostream>
#include <vector>

using namespace std;

string octal;
vector<int> binary;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> octal;
    
    if (octal == "0") {
        cout << 0;
        return 0;
    }
    
    for (int i=octal.length()-1; i>=0; --i) {
        int octal_digit = octal[i] - '0';
        for (int j=0; j<3; ++j) {
            binary.push_back((octal_digit>>j)&1);
        }
    }
    
    auto b = binary.rbegin();
    while (*b == 0) ++b;
    
    for (; b != binary.rend(); ++b)
        cout << *b;
    
    return 0;
}
