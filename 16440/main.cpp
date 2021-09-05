#include <iostream>
#include <vector>

using namespace std;

int n;
string cake;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> cake;
    
    int num_strawberry = 0;
    int num_kiwi = 0;
    
    for (int i = 0; i < n; i++) {
        if (cake[i] == 's') ++num_strawberry;
        else ++num_kiwi;
        
        if (i >= n/2) {
            if (cake[i - n/2] == 's') --num_strawberry;
            else --num_kiwi;
        }
        
        if (num_strawberry == n/4 && num_kiwi == n/4) {
            if (i == n/2 - 1) {
                cout << 1 << '\n' << i + 1;
            } else {
                cout << 2 << '\n' << i - n/2 + 1 << ' ' << i + 1;
            }
            
            break;
        }
    }
    
    return 0;
}
