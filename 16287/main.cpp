#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct sum {
    int value, i1, i2;
    
    sum(int v=0, int a=-1, int b=-1) :
    value(v), i1(a), i2(b) {}
    
    bool operator<(sum const& other) const {
        return value < other.value;
    }
};

const int MAX = 5000;
int n, w;
int arr[MAX];
vector<sum> twoSum;
vector<int> cache;

bool isDisjoint(sum const& x, sum const& y) {
    return (x.i1 != y.i1) && (x.i1 != y.i2)
        && (x.i2 != y.i1) && (x.i2 != y.i2);
}

bool findParcel(int lo, int hi) {
    if (lo >= hi) return false;
    
    int fourSum = twoSum[lo].value + twoSum[hi].value;
    if (fourSum < w) return findParcel(lo+1, hi);
    if (fourSum > w) return findParcel(lo, hi-1);
    if (isDisjoint(twoSum[lo], twoSum[hi])) return true;
    return findParcel(lo+1, hi) || findParcel(lo, hi-1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> w >> n;
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
        for (int j=0; j<i; ++j) {
            twoSum.push_back(sum(arr[i] + arr[j], j, i));
        }
    }
    sort(twoSum.begin(), twoSum.end());
    
    if (findParcel(0, twoSum.size()-1)) cout << "YES";
    else cout << "NO";
    
    return 0;
}
