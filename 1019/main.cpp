#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;

struct numSet {
    int num[10];
    
    numSet() {
        for (int &i : num) i = 0;
    }
    
    void fill(int start, int end, int value) {
        assert(0 <= start && start <= end && end < 10);
        for (int i=start; i<=end; ++i) {
            num[i] += value;
        }
    }
    
    numSet operator+(numSet const& other) const {
        numSet ret;
        for (int i=0; i<10; ++i) {
            ret.num[i] = num[i] + other.num[i];
        }
        return ret;
    }
    
    numSet operator-(numSet const& other) const {
        numSet ret;
        for (int i=0; i<10; ++i) {
            ret.num[i] = num[i] - other.num[i];
        }
        return ret;
    }
    
    numSet operator*(int x) const {
        numSet ret;
        for (int i=0; i<10; ++i) {
            ret.num[i] = num[i] * x;
        }
        return ret;
    }
};

int n;
numSet ans;

numSet solve_regular(int k) {
    /*
        Returns an answer for range [0, 10^k - 1],
            considering that all numbers in the range is k-digit number.
            (e.g. 123 is considered as 00123 if k == 5.)
    */
    numSet ret;
    ret.fill(0, 9, pow(10, k-1) * k);
    return ret;
}

numSet solve(int lo, int hi, int k) {
    numSet ret;
    int mod = pow(10, k);
    
    if (k == 0) {
        ret.fill(lo, hi, 1);
        return ret;
    }
    
    if (lo/mod != hi/mod) {
        ret.fill(lo/mod, hi/mod-1, mod);
        ret = ret + (solve_regular(k) * (hi/mod - lo/mod));
        ret = ret + solve(hi/mod * mod, hi, k);
    } else {
        ret.fill(lo/mod, hi/mod, hi-lo+1);
        ret = ret + solve(lo%mod, hi%mod, k-1);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
        
    int k = 0, mod = 1, tmp = n, zero = 0;
    while (tmp >= 10) {
        ++k;
        zero += mod;
        mod *= 10;
        tmp /= 10;
    }
    zero += mod;

    ans = solve(0, n, k);

    ans.num[0] -= zero;

    for (int &i : ans.num) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
