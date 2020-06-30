#include <iostream>

using namespace std;

struct vec {
    int x, y;
    
    vec(int xi = 0, int yi = 0) : x(xi), y(yi) {}
    
    vec operator-(vec const& other) const {
        return vec(x - other.x, y - other.y);
    }
    
    double crossProduct(vec const& other) const {
        return (x * other.y - y * other.x);
    }
};

double ccw(vec const& a, vec const& b, vec const& c) {
    // Returns a positive value if points a, b, c are in counterclockwise order.
    // Returns a negative value if points a, b, c are in clockwise order.
    // Returns a value approximate to 0 if points a, b, c are on the same line.
    return (b-a).crossProduct(c-a);
}

// If a value is in range [-EPSILON, EPSILON], then consider it as 0
const double EPSILON = 0.0001;
vec p[3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int x, y;
    for (int i=0; i<3; ++i) {
        cin >> x >> y;
        p[i] = vec(x, y);
    }
    
    double ccw_p = ccw(p[0], p[1], p[2]);
    if (ccw_p > EPSILON) cout << 1;
    else if (ccw_p < -1*EPSILON) cout << -1;
    else cout << 0;
    
    return 0;
}
