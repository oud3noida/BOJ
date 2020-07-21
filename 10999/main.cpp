#include <iostream>

using namespace std;

typedef long long bigInt;

const int MAX = 1000000;
int n, m, k;
bigInt arr[MAX], segTree[4*MAX], lazySegTree[4*MAX];

bigInt _makeSegTree(int cur, int left, int right) {
    int mid = (left + right) / 2;
    lazySegTree[cur] = 0;
    
    if (left == right) return segTree[cur] = arr[left];
    
    return segTree[cur] =
           _makeSegTree(2*cur+1, left, mid) + _makeSegTree(2*cur+2, mid+1, right);
}

void makeSegTree() {
    _makeSegTree(0, 0, n-1);
}

void propagate(int cur, int curLeft, int curRight) {
    if (lazySegTree[cur] == 0) return;
    
    segTree[cur] += lazySegTree[cur] * (curRight - curLeft + 1);
    if (curLeft != curRight) {
        lazySegTree[2*cur+1] += lazySegTree[cur];
        lazySegTree[2*cur+2] += lazySegTree[cur];
    }
    lazySegTree[cur] = 0;
}

void _update(int queryLeft, int queryRight, int cur, int curLeft, int curRight, bigInt x) {
    int curMid = (curLeft + curRight) / 2;
    
    propagate(cur, curLeft, curRight);
    
    if (curRight < queryLeft || queryRight < curLeft)
        return;
    if (queryLeft <= curLeft && curRight <= queryRight) {
        lazySegTree[cur] += x;
        propagate(cur, curLeft, curRight);
        return;
    }
    
    _update(queryLeft, queryRight, 2*cur+1, curLeft, curMid, x);
    _update(queryLeft, queryRight, 2*cur+2, curMid+1, curRight, x);
    
    segTree[cur] = segTree[2*cur+1] + segTree[2*cur+2];
}

void update(int left, int right, bigInt x) {
    _update(left, right, 0, 0, n-1, x);
}

bigInt _query(int queryLeft, int queryRight, int cur, int curLeft, int curRight) {
    int curMid = (curLeft + curRight) / 2;
    
    propagate(cur, curLeft, curRight);
    
    if (curRight < queryLeft || queryRight < curLeft)
        return 0;
    if (queryLeft <= curLeft && curRight <= queryRight)
        return segTree[cur];
    
    return _query(queryLeft, queryRight, 2*cur+1, curLeft, curMid)
         + _query(queryLeft, queryRight, 2*cur+2, curMid+1, curRight);
}

bigInt query(int left, int right) {
    return _query(left, right, 0, 0, n-1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i=0; i<n; ++i) cin >> arr[i];
    
    makeSegTree();
    
    int a, b, c;
    bigInt d;
    for (int i=0; i<m+k; ++i) {
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            update(b-1, c-1, d);
        } else if (a == 2) {
            cin >> b >> c;
            cout << query(b-1, c-1) << "\n";
        }
    }
    
    return 0;
}
