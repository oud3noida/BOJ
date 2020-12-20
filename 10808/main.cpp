#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string s;
    cin >> s;

    vector<int> num_alphabet(26, 0);
    for (int i=0; i<s.length(); ++i) ++num_alphabet[s[i] - 'a'];
    for (int i=0; i<26; ++i) cout << num_alphabet[i] << " ";

    return 0;
}