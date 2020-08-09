#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 0.00001, INF = 987654321;

struct Vector2 {
    double x, y;
    
    explicit Vector2(double x=0, double y=0) : x(x), y(y) {}
    
    bool operator<(const Vector2& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x-other.x, y-other.y);
    }
    
    Vector2 operator*(double v) const {
        return Vector2(x*v, y*v);
    }
    
    double norm() {
        return sqrt(x*x + y*y);
    }
    
    double dot(const Vector2& other) const {
        return x*other.x + y*other.y;
    }
    
    double cross(const Vector2& other) const {
        return x*other.y - y*other.x;
    }
    
    bool isPerpFootOnSegment(Vector2 a, Vector2 b) const {
        /*
            Returns true if there exists a perpendicular foot from this point
             to a line segment with endpoints 'a' and 'b'.
            Otherwise returns false.
        */
        Vector2 c = Vector2(x, y);
        return (c-a).dot(b-a) * (c-b).dot(a-b) > -1*EPSILON;
    }
};

double distance_point_segment(Vector2 p, Vector2 a, Vector2 b) {
    /*
        Returns a distance between a point 'p'
         and a line segment with endpoints 'a' and 'b'.
    */
    if (p.isPerpFootOnSegment(a, b))
        return fabs((b-a).cross(p-a)) / (b-a).norm();
    return min((p-a).norm(), (p-b).norm());
}

int n, m;
vector<pair<Vector2, Vector2>> sinchon;
double ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    ans = INF;
    
    double xs, ys, xe, ye;
    for (int yon=0; yon<n; ++yon) {
        cin >> xs >> ys >> xe >> ye;
        sinchon.push_back(make_pair(Vector2(xs, ys), Vector2(xe, ye)));
    }
    for (int ko=0; ko<m; ++ko) {
        cin >> xs >> ys >> xe >> ye;
        Vector2 vc = Vector2(xs, ys),
                vd = Vector2(xe, ye);
        for (int yon=0; yon<n; ++yon) {
            Vector2 va = sinchon[yon].first,
                    vb = sinchon[yon].second;
            ans = min(ans, distance_point_segment(va, vc, vd));
            ans = min(ans, distance_point_segment(vb, vc, vd));
            ans = min(ans, distance_point_segment(vc, va, vb));
            ans = min(ans, distance_point_segment(vd, va, vb));
        }
    }
    
    cout.precision(16);
    cout << ans << endl;
    
    return 0;
}
