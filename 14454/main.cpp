#include <iostream>

using namespace std;

int n;
long long k;
string s;

char ith_character(long long i) {
    if (i < n) return s[i];
    
    long long j = i / n;
    while ((j & (j-1)) != 0) {
        j &= (j-1);
    }
    
    if (i == j*n) return ith_character(j*n - 1);
    else return ith_character(i - j*n - 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> s >> k;
    n = s.length();
    
    cout << ith_character(k-1);
    
    return 0;
}
