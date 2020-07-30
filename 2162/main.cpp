#include <iostream>
#include <vector>

using namespace std;

struct Vec {
    int x, y;
    
    Vec(int x=0, int y=0) : x(x), y(y) {}
    
    bool operator<(const Vec &other) const {
        if (x != other.x) return x < other.x;
        else return y < other.y;
    }
};

typedef pair<Vec, Vec> LineSeg;

int N, numGroup, maxGroupSize;
vector<LineSeg> segments;
vector<int> groupID, groupSize;

int ccw(const Vec &a, const Vec &b, const Vec &c) {
    int ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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

int find(int i) {
    if (i != groupID[i]) return groupID[i] = find(groupID[i]);
    return i;
}

void merge(int a, int b) {
    int groupA = find(a), groupB = find(b);
    
    if (groupA == groupB) return;
    
    if (groupSize[groupA] > groupSize[groupB]) swap(groupA, groupB);
    
    --numGroup;
    groupID[groupA] = groupB;
    groupSize[groupB] += groupSize[groupA];
    maxGroupSize = max(maxGroupSize, groupSize[groupB]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    int a, b, c, d;
    for (int i=0; i<N; ++i) {
        cin >> a >> b >> c >> d;
        segments.push_back(make_pair(Vec(a, b), Vec(c, d)));
        groupID.push_back(i);
        groupSize.push_back(1);
    }
    numGroup = N;
    maxGroupSize = 1;
    
    for (int i=1; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            if (segIntersect(segments[i], segments[j])) {
                merge(i, j);
            }
        }
    }
    
    cout << numGroup << "\n" << maxGroupSize;
    
    return 0;
}
