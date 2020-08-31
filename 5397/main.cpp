#include <iostream>
#include <list>

using namespace std;

int T;
string L;
list<char> password;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for (int t=0; t<T; ++t) {
        cin >> L;
        int len = L.length();
        
        password.clear();
        auto it = password.begin();
        for (int i=0; i<len; ++i) {
            switch (L[i]) {
                case '<':
                    if (it != password.begin()) --it;
                    break;
                case '>':
                    if (it != password.end()) ++it;
                    break;
                case '-':
                    if (it != password.begin()) it = password.erase(--it);
                    break;
                default:
                    it = password.insert(it, L[i]);
                    if (it != password.end()) ++it;
            }
        }
        
        for (char c : password) cout << c;
        cout << "\n";
    }
    
    return 0;
}
