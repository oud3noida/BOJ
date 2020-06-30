#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct vec {
    int x, y;
    
    vec(int xi = 0, int yi = 0) : x(xi), y(yi) {}
    
    vec operator-(vec const& other) const {
        return vec(x - other.x, y - other.y);
    }
    
    double crossProduct(vec const& other) const {
        return (1LL * x * other.y - 1LL * y * other.x);
    }
    
    bool operator<(vec const& other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
    
    double norm() const {
        return sqrt(1LL * x * x + 1LL * y * y);
    }
};

double ccw(vec const& a, vec const& b, vec const& c) {
    /* 
        Returns a positive value if points a, b, c are in counterclockwise order.
        Returns a negative value if points a, b, c are in clockwise order.
        Returns a value approximate to 0 if points a, b, c are on the same line.
    */
    return (b-a).crossProduct(c-a);
}

// If a value is in range [-EPSILON, EPSILON], then consider it as 0
const double EPSILON = 0.0001;
int n;
vector<vec> points, convexHull;
vec pivot;

bool compCCW(vec const& a, vec const& b) {
    /*
        If CCW(pivot, a, b) > 0, returns true.
        If CCW(pivot, a, b) == 0 and |a-pivot| < |b-pivot|, returns true.
        Otherwise, returns false.
    */
    double ret = ccw(pivot, a, b);
    if (fabs(ret) > EPSILON) return ret > 0;
    else return (a-pivot).norm() < (b-pivot).norm();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    int a, b;
    for (int i=0; i<n; ++i) {
        cin >> a >> b;
        points.push_back(vec(a, b));
    }
    
    // Set pivot
    auto start = min_element(points.begin(), points.end());
    pivot = *start;
    iter_swap(points.begin(), start);
    
    // Sort points in counterclockwise order
    sort(points.begin()+1, points.end(), compCCW);
    
    // Find points on the convex hull
    auto cur = points.begin();
    for (int i=0; i<n+1; ++i) {
        convexHull.push_back(*cur);
        if (convexHull.size() < 3) {
            if (i == n-1) cur = points.begin();
            else ++cur;
            continue;
        }
        
        while (convexHull.size() >= 3) {
            auto a = (convexHull.end() - 3),
                 b = (convexHull.end() - 2),
                 c = (convexHull.end() - 1);
            
            double ccwCur = ccw(*a, *b, *c);
            // If CCW(a, b, c) < 0, remove b from the convex hull
            if (ccwCur < -1*EPSILON) convexHull.erase(b);
            // If CCW(a, b, c) == 0, remove b or c from the convex hull as following:
            else if (ccwCur < EPSILON) {
                // If |b-a| < |c-a|, remove b from the convex hull
                if ((*b - *a).norm() < (*c - *a).norm()) convexHull.erase(b);
                // If |c-a| < |b-a|, remove c from the convex hull
                else convexHull.erase(c);
            }
            // If CCW(a, b, c) > 0, end the loop
            else break;
        }
        
        // If 'cur' points to the last element, move back to the first element
        // Otherwise move on to the next element
        if (i == n-1) cur = points.begin();
        else ++cur;
    }
    
    cout << convexHull.size() - 1;
    
    return 0;
}
