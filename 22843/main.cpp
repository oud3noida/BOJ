#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vector2 {
    double x, y;
    
    Vector2(double x=0, double y=0) : x(x), y(y) {}
    
    Vector2 operator-(const Vector2 &other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    double dot(const Vector2 &other) const {
        return x * other.x + y * other.y;
    }
    
    double cross(const Vector2 &other) const {
        return x * other.y - y * other.x;
    }
    
    double norm_squared() const {
        return x*x + y*y;
    }
    
    Vector2 normalized() const {
        double norm = sqrt(norm_squared());
        return Vector2(x / norm, y / norm);
    }
    
    bool operator<(const Vector2& other) const {
        // Return theta(this) < theta(other)
        Vector2 theta_zero(1, 0);
        
        if (y == 0 && other.y == 0) return x > other.x; // theta1, theta2 = 0 or pi
        if (y * other.y < 0) return y > other.y;        // 0 < theta1 < pi and pi < theta2 < 2pi
        double cos_theta_this = theta_zero.dot(normalized()),
               cos_theta_other = theta_zero.dot(other.normalized());
        if (y > 0 || other.y > 0) return cos_theta_this > cos_theta_other;
        return cos_theta_this < cos_theta_other;
    }
};

struct Segment {
    Vector2 p1, p2;
    
    Segment(Vector2 p1=Vector2(), Vector2 p2=Vector2()) : p1(p1), p2(p2) {}
    
    double gradient() const {
        return (p2.y - p1.y) / (p2.x - p1.x);
    }
};

constexpr double EPSILON = 0.000001;
constexpr double MAX = 10'000;
vector<Vector2> houses;
vector<Vector2> SQUARE_POINTS;
vector<Segment> SQUARE_EDGES;

bool closer(const Vector2& p, const Vector2 &a, const Vector2 &b) {
    return (a-p).norm_squared() - (b-p).norm_squared() < EPSILON;
}

bool closest(const Vector2& p) {
    return closer(p, houses[0], houses[1]) && closer(p, houses[0], houses[2]);
}

bool in_range(const Vector2& p) {
    return 0 <= p.x && p.x <= MAX && 0 <= p.y && p.y <= MAX;
}

Vector2 middle(const Vector2& a, const Vector2& b) {
    return Vector2((a.x + b.x) / 2, (a.y + b.y) / 2);
}

Segment bisector(const Vector2& a, const Vector2& b) {
    Vector2 p1 = middle(a, b);
    if (a.y == b.y) {
        Vector2 p2(p1.x, p1.y + 1);
        return Segment(p1, p2);
    }
    
    double dy = -1 / Segment(a, b).gradient();
    Vector2 p2(p1.x + 1, p1.y + dy);
    return Segment(p1, p2);
}

Vector2 intersection(const Segment& l1, const Segment& l2) {
    double x1 = l1.p1.x,
           x2 = l2.p1.x,
           y1 = l1.p1.y,
           y2 = l2.p1.y;
           
    if (abs(l1.p1.x - l1.p2.x) < EPSILON) { // Gradient1 == INF
        double g2 = l2.gradient();
        return Vector2(x1, g2*(x1-x2)+y2);
    }
    if (abs(l2.p1.x - l2.p2.x) < EPSILON) { // Gradient2 == INF
        double g1 = l1.gradient();
        return Vector2(x2, g1*(x2-x1)+y1);
    }
    
    double g1 = l1.gradient(),
           g2 = l2.gradient();
    if (abs(g1 - g2) < EPSILON) return Vector2(-1, -1);
    
    double x_i = (g1*x1 - g2*x2 - (y1 - y2)) / (g1 - g2);
    double y_i = g1*(x_i - x1) + y1;
    
    return Vector2(x_i, y_i);
}

double answer() {
    vector<Segment> bisectors = {
        bisector(houses[0], houses[1]),
        bisector(houses[0], houses[2])
    };
    
    vector<Vector2> intersections;
    
    Vector2 intersection_bisectors = intersection(bisectors[0], bisectors[1]);
    if (in_range(intersection_bisectors) && closest(intersection_bisectors)) {
        intersections.push_back(intersection_bisectors - houses[0]);
    }
    
    for (auto bi : bisectors) {
        for (auto edge : SQUARE_EDGES) {
            Vector2 intersection_edge = intersection(bi, edge);
            if (in_range(intersection_edge) && closest(intersection_edge)) {
                intersections.push_back(intersection_edge - houses[0]);
            }
        }
    }
    
    for (auto square_point : SQUARE_POINTS) {
        if (closest(square_point)) {
            intersections.push_back(square_point - houses[0]);
        }
    }
    
    sort(intersections.begin(), intersections.end());
    
    double ret = 0;
    
    for (int i=0; i<intersections.size(); ++i) {
        double area_triangle = 0;
        if (i == 0) {
            area_triangle = 0.5 * intersections[intersections.size() - 1].cross(intersections[i]);
        } else {
            area_triangle = 0.5 * intersections[i-1].cross(intersections[i]);
        }
        
        if (area_triangle < 0) continue;
        ret += area_triangle;
    }
    
    return ret / (MAX*MAX);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cout << fixed;
    
    SQUARE_POINTS = {
        Vector2(0, 0),
        Vector2(MAX, 0),
        Vector2(MAX, MAX),
        Vector2(0, MAX)
    };
    SQUARE_EDGES = {
        Segment(SQUARE_POINTS[0], SQUARE_POINTS[1]),
        Segment(SQUARE_POINTS[1], SQUARE_POINTS[2]),
        Segment(SQUARE_POINTS[2], SQUARE_POINTS[3]),
        Segment(SQUARE_POINTS[3], SQUARE_POINTS[0])
    };
    
    int x, y;
    for (int t=1; ; ++t) {
        houses.clear();
        for (int i=0; i<3; ++i) {
            cin >> x >> y;
            houses.emplace_back(x, y);
        }
        
        bool done = true;
        for (int i=0; i<3; ++i) {
            if (houses[i].x != 0 || houses[i].y != 0) {
                done = false;
                break;
            }
        }
        if (done) return 0;
        
        cout << t << ' ' << answer() << '\n';
    }
    
    return 0;
}
