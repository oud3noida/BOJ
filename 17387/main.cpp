#include <iostream>

using namespace std;

struct Vec {
    long long x, y;
    
    Vec(long long x=0, long long y=0) : x(x), y(y) {}
    
    bool operator<(const Vec &other) const {
        if (x != other.x) return x < other.x;
        else return y < other.y;
    }
};

typedef pair<Vec, Vec> LineSeg;

int ccw(const Vec &a, const Vec &b, const Vec &c) {
    long long ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (ret > 0) return 1;
    if (ret < 0) return -1;
    return 0;
}

bool segIntersect(const LineSeg &ab, const LineSeg &cd) {
    Vec a = ab.first, b = ab.second,
        c = cd.first, d = cd.second;
    int ccw1 = ccw(a, b, c) * ccw(a, b, d),
        ccw2 = ccw(c, d, a) * ccw(c, d, b);
    
    if (ccw1 == 0 && ccw2 == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c || d < a);
    }
    return ccw1 <= 0 && ccw2 <= 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    LineSeg segments[2];
    
    int a, b, c, d;
    
    for (int i=0; i<2; ++i) {
        cin >> a >> b >> c >> d;
        segments[i] = make_pair(Vec(a, b), Vec(c, d));
    }
    
    cout << (segIntersect(segments[0], segments[1]) ? 1 : 0);
    
    return 0;
}
