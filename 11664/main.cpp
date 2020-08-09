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
    
    bool operator==(const Vector3& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }
    
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x+other.x, y+other.y, z+other.z);
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x-other.x, y-other.y, z-other.z);
    }
    
    Vector3 operator*(double v) const {
        return Vector3(x*v, y*v, z*v);
    }
    
    double norm_squared() {
        return x*x + y*y + z*z;
    }
    
    double norm() {
        return sqrt(norm_squared());
    }
    
    int dot(const Vector3& other) const {
        return x*other.x + y*other.y + z*other.z;
    }
    
    Vector3 normalize() {
        return Vector3(x, y, z) * (1/norm());
    }
    
    bool perpendicularFoot(Vector3 a, Vector3 b, Vector3& p) const {
        /*
            Returns a perpendicular foot 'p' on a line segment with endpoints 'a' and 'b'.
            If a perpendicular foot lies on the line segment, returns true.
            Otherwise, returns false.
        */
        if (b < a) swap(a, b);
        Vector3 c = Vector3(x, y, z);
        p = (b-a).normalize() * ((c-a).dot(b-a) * 1/(b-a).norm()) + a;
        if (p < a || b < p) return false;
        return true;
    }
};

double distance_point_segment(Vector3 p, Vector3 a, Vector3 b) {
    /*
        Returns a distance between a point 'p'
         and a line segment with endpoints 'a' and 'b'.
    */
    if (b < a) swap(a, b);
    Vector3 p_ab;
    if (p.perpendicularFoot(a, b, p_ab)) {
        double distance_squared = (p-a).norm_squared() - (p_ab-a).norm_squared();
        if (distance_squared < EPSILON) return 0;
        return sqrt(distance_squared);
    }
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
