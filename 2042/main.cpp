#include <iostream>

using namespace std;

typedef long long bigInt;

const int MAX = 1000000;
int n, m, k;
bigInt arr[MAX+1], fenwick[MAX+1];

constexpr int lsb(int x) {
    return x & -x;
}

void update(int idx, bigInt x) {
    bigInt dx = x - arr[idx];
    
    arr[idx] += dx;
    while (idx <= n) {
        fenwick[idx] += dx;
        idx += lsb(idx);
    }
}

bigInt findPSum(int from, int to) {
    if (from > 0)
        return findPSum(0, to) - findPSum(0, from-1);
    
    if (to == 0) return 0;
    
    bigInt ret = 0;
    while (to > 0) {
        ret += fenwick[to];
        to -= lsb(to);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i=1; i<=n; ++i) {
        cin >> arr[i];
        fenwick[i] = arr[i];
        if (i%2 == 1) continue;
        for (int j=(i-lsb(i))+1; j<i; ++j) {
            fenwick[i] += arr[j];
        }
    }
    
    int a, b;
    bigInt c;
    for (int i=0; i<m+k; ++i) {
        cin >> a >> b >> c;
        if (a == 1) update(b, c);
        else cout << findPSum(b, c) << "\n";
    }
    
    return 0;
}