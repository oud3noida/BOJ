#include <iostream>

using namespace std;

long long a, b;

long long ones_log2(int i) {
    /* Calculates the answer for range [0, 2^i). */
    return i * (1LL<<(i-1));
}

long long ones(long long start, long long end) {
    /* Calculates the answer for range [A, B]. */
    if (start != 0) return ones(0, end) - ones(0, start-1);
    
    long long x = end, ret = 0,
              leadingOne = end+1;
    for (int i=63; i>=0; i--) {
        if (!(x & (1LL<<i))) continue;
        leadingOne -= (1LL<<i);
        ret += ones_log2(i) + leadingOne;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> a >> b;
    cout << ones(a, b);
    
    return 0;
}
