#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    string s;
    getline(cin, s);

    for (char c : s) {
        if ('A' <= c && c <= 'Z') cout << (char) ((c - 'A' + 13) % 26 + 'A');
        else if ('a' <= c && c <= 'z') cout << (char) ((c - 'a' + 13) % 26 + 'a');
        else cout << c;
    }

    return 0;
}