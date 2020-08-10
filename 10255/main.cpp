#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Vector2 {
    int x, y;
    
    explicit Vector2(int x=0, int y=0) : x(x), y(y) {}
    
    bool operator<(const Vector2& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x-other.x, y-other.y);
    }
    
    int cross(const Vector2& other) const {
        return x*other.y - y*other.x;
    }
};

typedef pair<Vector2, Vector2> Segment;

int ccw(const Vector2& a, const Vector2& b, const Vector2& c) {
    int ret = (b-a).cross(c-a);
    if (ret > 0) return 1;
    if (ret < 0) return -1;
    return 0;
}

int intersection_seg_point(const Segment& ab, const Vector2& p) {
    /*
        Returns 1 if a point 'p' lies on a line segment 'ab'.
        Returns 0 otherwise.
    */
    Vector2 a = ab.first, b = ab.second;
    if (b < a) swap(a, b);
    return ((!((p < a) || (b < p)) && ccw(a, p, b) == 0) ? 1 : 0);
}

int intersection_seg_seg(const Segment& ab, const Segment& cd) {
    /*
        Returns the number of points where two line segments 'ab' and 'cd' intersect.
        If the number of points are infinite, returns 4.
        -- NOTICE: endpoints of the line segment 'ab' are not counted in. --
    */
    Vector2 a = ab.first, b = ab.second,
            c = cd.first, d = cd.second;
    
    int ccw_abc = ccw(a, b, c),
        ccw_abd = ccw(a, b, d),
        ccw_ab = ccw_abc * ccw_abd,
        ccw_cd = ccw(c, d, a) * ccw(c, d, b);
    
    if (ccw_abc == 0 && ccw_abd == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        
        // If two segments intersect at one of the endpoints of 'ab',
        //  or if two segments are parallel but do not intersect, return 0
        if (a == d || b == c || d < a || b < c) return 0;
        // If two segments have an infinite number of intersection points, return 4
        return 4;
    }
    // If two segments intersect at one point (other than 'a' or 'b'), return 1
    if (ccw_ab < 0 && ccw_cd <= 0) return 1;
    // Otherwise, return 0
    return 0;
}

int T, ans;
vector<Segment> rectangle;
Segment lineSeg;

void makeRectanlge(int xmin, int ymin, int xmax, int ymax) {
    rectangle.clear();
    rectangle.push_back(make_pair(Vector2(xmin, ymin), Vector2(xmin, ymax)));
    rectangle.push_back(make_pair(Vector2(xmin, ymax), Vector2(xmax, ymax)));
    rectangle.push_back(make_pair(Vector2(xmax, ymax), Vector2(xmax, ymin)));
    rectangle.push_back(make_pair(Vector2(xmax, ymin), Vector2(xmin, ymin)));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    
    int a, b, c, d;
    for (int i=0; i<T; ++i) {
        ans = 0;
        cin >> a >> b >> c >> d;
        makeRectanlge(a, b, c, d);
        cin >> a >> b >> c >> d;
        lineSeg = make_pair(Vector2(a, b), Vector2(c, d));
        for (auto &edge : rectangle) {
            ans += intersection_seg_point(lineSeg, edge.first);
            ans += intersection_seg_seg(lineSeg, edge);
        }
        cout << (ans < 4 ? ans : 4) << "\n";
    }
    
    return 0;
}
