#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    
    Point(int x=0, int y=0) : x(x), y(y) {}
    
    bool operator<=(const Point& other) const {
        return x <= other.x && y <= other.y;
    }
};

typedef pair<Point, Point> Rectangle;

int N, ans;
vector<Rectangle> rectangles;
vector<int> parent;

bool rectanglesIntersect(Rectangle a, Rectangle b) {
    int a_x1 = a.first.x,
        a_x2 = a.second.x,
        a_y1 = a.first.y,
        a_y2 = a.second.y,
        b_x1 = b.first.x,
        b_x2 = b.second.x,
        b_y1 = b.first.y,
        b_y2 = b.second.y;
    
    bool overlapping = !(a_x2 < b_x1 || b_x2 < a_x1) &&
                       !(a_y2 < b_y1 || b_y2 < a_y1),
         including = ((a_x1 < b_x1 && b_x2 < a_x2) &&
                      (a_y1 < b_y1 && b_y2 < a_y2)) ||
                     ((b_x1 < a_x1 && a_x2 < b_x2) &&
                      (b_y1 < a_y1 && a_y2 < b_y2));
    return overlapping && !including;
}

int find(int x) {
    if (x != parent[x]) return parent[x] = find(parent[x]);
    return x;
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    
    if (a == b) return;
    parent[b] = a;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    ans = N;
    rectangles.push_back(make_pair(Point(0, 0), Point(0, 0)));
    parent.push_back(0);
    
    int x1, y1, x2, y2;
    for (int i=1; i<=N; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        rectangles.push_back(make_pair(Point(x1, y1), Point(x2, y2)));
        parent.push_back(i);
        for (int j=0; j<i; ++j) {
            if (rectanglesIntersect(rectangles[i], rectangles[j])) {
                if (find(i) != find(j)) --ans;
                merge(i, j);
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
