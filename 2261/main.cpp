#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y, id;
    
    Point(int x, int y, int id) : x(x), y(y), id(id) {}
    
    bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
    
    int distance_squared(const Point& other) const {
        return (x - other.x) * (x - other.x) +
               (y - other.y) * (y - other.y);
    }
};

constexpr int INF = 1'987'654'321,
              MAX = 10'000;
int num_points;
vector<Point> points;
vector<vector<Point>> points_by_x;

int min_distance_squared() {
    int d = INF;
    
    for (auto it = next(points.begin()); it != points.end(); ++it) {
        d = min(d, prev(it)->distance_squared(*it));
    }
    
    for (auto p1 = points.begin(); p1 != points.end(); ++p1) {       
        int x_begin = p1->x - ceil(sqrt(d)) + MAX,
            x_end = p1->x + ceil(sqrt(d)) + MAX;
        
        for (int x_it = max(x_begin, 0); x_it <= min(x_end, 2*MAX); ++x_it) {
            int y_begin = p1->y - ceil(sqrt(d)),
                y_end = p1->y + ceil(sqrt(d));
            
            auto it_begin = lower_bound(points_by_x[x_it].begin(),
                                        points_by_x[x_it].end(),
                                        Point(x_it - MAX, y_begin, -1));
            auto it_end = lower_bound(points_by_x[x_it].begin(),
                                      points_by_x[x_it].end(),
                                      Point(x_it - MAX, y_end, -1));
            
            for (auto p2 = it_begin; p2 != it_end; ++p2) {
                if (p1->id != p2->id && (p1->distance_squared(*p2)) < d) {
                    d = p1->distance_squared(*p2);
                }
            }
        }
    }
    
    return d;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_points;
    
    points_by_x.assign(2*MAX + 1, vector<Point>());
    
    int x, y;
    for (int i=0; i<num_points; ++i) {
        cin >> x >> y;
        points.emplace_back(x, y, i);
        points_by_x[x + MAX].emplace_back(x, y, i);
    }
    
    sort(points.begin(), points.end());
    for (int i=0; i<=2*MAX; ++i) {
        sort(points_by_x[i].begin(), points_by_x[i].end());
    }
    
    cout << min_distance_squared();
    
    return 0;
}
