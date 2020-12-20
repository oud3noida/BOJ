#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    getline(cin, s);
    int s_len = s.length();
    int word_len = 0;

    bool tag = false;
    for (int i=0; i<s_len; ++i) {
        if (s[i] == '<') {
            tag = true;
            if (word_len != 0) {
                for (int x=1; x<=word_len; ++x) cout << s[i-x];
                word_len = 0;
            }
        }

        if (tag) {
            cout << s[i];
            if (s[i] == '>') tag = false;
            continue;
        } else {
            if (s[i] == ' ') {
                for (int x=1; x<=word_len; ++x) cout << s[i-x];
                word_len = 0;
                cout << s[i];
            } else {
                word_len++;
            }
        }
    }

    if (word_len != 0) {
        for (int x=1; x<=word_len; ++x) cout << s[s_len-x];
        word_len = 0;
    }

    return 0;
}