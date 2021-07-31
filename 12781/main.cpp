#include <iostream>
#include <vector>

using namespace std;

struct Vector2 {
    int x, y;
    
    Vector2(int x, int y) : x(x), y(y) {}
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    int cross(const Vector2& other) const {
        return x*other.y - y*other.x;
    }
};

int ccw(Vector2 a, Vector2 b, Vector2 c) {
    return (b-a).cross(c-a);
}

struct Segment {
    Vector2 p1, p2;
    
    Segment(Vector2 p1, Vector2 p2) : p1(p1), p2(p2) {}
    
    bool intersect(const Segment& other) const {
        long long ccw1 = ccw(p1, p2, other.p1),
                  ccw2 = ccw(p1, p2, other.p2);
        return ccw1 * ccw2 < 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int x, y;
    vector<Segment> lines;
    for (int i=0; i<2; ++i) {
        vector<Vector2> points;
        for (int j=0; j<2; ++j) {
            cin >> x >> y;
            points.emplace_back(x, y);
        }
        lines.emplace_back(points[0], points[1]);
        points.clear();
    }
    
    cout << (lines[0].intersect(lines[1]) ? 1 : 0);
    
    return 0;
}
