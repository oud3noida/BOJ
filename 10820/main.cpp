#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    string s;

    while (!cin.eof()) {
        getline(cin, s);

        vector<int> analysis(4, 0);
        for (int i = 0; i < s.length(); ++i) {
            if ('a' <= s[i] && s[i] <= 'z') ++analysis[0];
            else if ('A' <= s[i] && s[i] <= 'Z') ++analysis[1];
            else if ('0' <= s[i] && s[i] <= '9') ++analysis[2];
            else if (s[i] == ' ') ++analysis[3];
        }

        if (analysis[0] + analysis[1] + analysis[2] + analysis[3] == 0) continue;

        for (int x : analysis) cout << x << " ";
        cout << "\n";
    }

    return 0;
}