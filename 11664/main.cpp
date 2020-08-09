#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 0.00001;

struct Vector3 {
    double x, y, z;
    
    explicit Vector3(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
    
    bool operator<(const Vector3& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x-other.x, y-other.y, z-other.z);
    }
    
    Vector3 operator*(double v) const {
        return Vector3(x*v, y*v, z*v);
    }
    
    double norm_squared() const {
        return x*x + y*y + z*z;
    }
    
    double norm() const {
        return sqrt(norm_squared());
    }
    
    double dot(const Vector3& other) const {
        return x*other.x + y*other.y + z*other.z;
    }
    
    double cross(const Vector3& other) const {
        double aabb = norm_squared() * other.norm_squared();
        double abab = dot(other) * dot(other);
        return sqrt(fabs(aabb - abab));
    }
    
    bool isPerpFootOnSegment(Vector3 a, Vector3 b) const {
        /*
            Returns true if there exists a perpendicular foot from this point
             to a line segment with endpoints 'a' and 'b'.
            Otherwise returns false.
        */
        Vector3 c = Vector3(x, y, z);
        return (c-a).dot(b-a) * (c-b).dot(a-b) > -1*EPSILON;
    }
};

double distance_point_segment(Vector3 p, Vector3 a, Vector3 b) {
    /*
        Returns a distance between a point 'p'
         and a line segment with endpoints 'a' and 'b'.
    */
    if (p.isPerpFootOnSegment(a, b))
        return fabs((b-a).cross(p-a)) / (b-a).norm();
    return min((p-a).norm(), (p-b).norm());
}

vector<Vector3> points;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int x, y, z;
    for (int i=0; i<3; ++i) {
        cin >> x >> y >> z;
        points.push_back(Vector3(x, y, z));
    }
    
    cout.precision(16);
    cout << distance_point_segment(points[2], points[0], points[1]);
    
    return 0;
}
