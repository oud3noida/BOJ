#include <iostream>
#include <vector>

using namespace std;

string query;
bool ans;
vector<string> NeverGonna = {"Give you up",
                             "Let you down",
                             "Run around and desert you",
                             "Make you cry",
                             "Say goodbye",
                             "Tell a lie and hurt you"};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    getline(cin, query);
    ans = true;
    for (int i=0; i<NeverGonna.size(); ++i) {
        if (NeverGonna[i] == query) ans = false;
    }
    
    if (ans) cout << "YES";
    else cout << "NO";
    
    return 0;
}
