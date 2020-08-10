#include <iostream>
#include <vector>

using namespace std;

struct Vector2 {
    int x, y;
    
    explicit Vector2(int x=0, int y=0) : x(x), y(y) {}
    
    bool operator<(const Vector2& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x-other.x, y-other.y);
    }
    
    int cross(const Vector2& other) const {
        return x*other.y - y*other.x;
    }
};

int ccw(const Vector2& a, const Vector2& b, const Vector2& c) {
    int ret = (b-a).cross(c-a);
    if (ret > 0) return 1;
    if (ret < 0) return -1;
    return 0;
}

bool segIntersect(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    /*
        Returns true if two line segments 'ab' and 'cd' intersect.
        Returns false otherwise.
    */
    int ccw_ab = ccw(a, b, c) * ccw(a, b, d),
        ccw_cd = ccw(c, d, a) * ccw(c, d, b);
    
    if (ccw_ab == 0 && ccw_cd == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(d < a || b < c);
    }
    return (ccw_ab <= 0 && ccw_cd <= 0);
}

int N;
vector<Vector2> robots, shelters;
vector<int> ans;

bool evacuate(int cur, int occupied) {
    cout << cur << ": ";
    for (int i : ans) cout << i+1 << " ";
    cout << endl;
    
    if (cur == N) return true;
    
    for (int i=0; i<N; ++i) {
        if (occupied & (1<<i)) continue;
        
        bool collide = false;
        for (int j=0; j<cur; ++j) {
            if (segIntersect(robots[j], shelters[ans[j]], robots[cur], shelters[i])) {
                collide = true;
                break;
            }
        }
        if (collide) continue;
        
        ans[cur] = i;
        if (evacuate(cur+1, occupied | (1<<i))) return true;
    }
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    int lat, lng;
    for (int i=0; i<N; ++i) {
        cin >> lat >> lng;
        robots.push_back(Vector2(lat, lng));
    }
    for (int i=0; i<N; ++i) {
        cin >> lat >> lng;
        shelters.push_back(Vector2(lat, lng));
    }
    
    ans.assign(N, -1);
    evacuate(0, 0);
    for (int i : ans) cout << i+1 << "\n";
    
    return 0;
}
