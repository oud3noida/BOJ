#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 1'987'654'321;

struct Vector2 {
    int x, y;
    
    Vector2(int x, int y) : x(x), y(y) {}
    
    double norm() {
        return sqrt(x*x + y*y);
    }
};

Vector2 operator-(const Vector2& a, const Vector2& b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

int n;
vector<Vector2> amenities;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    int x, y;
    for (int i=0; i<n; ++i) {
        cin >> x >> y;
        amenities.emplace_back(x, y);
    }
    
    double min_average = INF;
    int house_candidate = 0;
    for (int i=0; i<n; ++i) {
        double max_distance = 0;
        for (int j=0; j<n; ++j) {
            max_distance = max(max_distance, (amenities[i] - amenities[j]).norm());
        }
        if (min_average > max_distance) {
            min_average = max_distance;
            house_candidate = i;
        }
    }
    
    cout << amenities[house_candidate].x << ' ' << amenities[house_candidate].y;

    return 0;
}
