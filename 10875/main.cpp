#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int INF = 987654321;
const int DX[4] = {1, 0, -1, 0},
          DY[4] = {0, 1, 0, -1};
int L, N, dir;
long long ans;

struct Vector2 {
    int x, y;
    
    Vector2(int x=0, int y=0) : x(x), y(y) {}
    
    bool operator<(const Vector2& other) const {
        return (x != other.x) ? x < other.x : y < other.y;
    }
    
    bool operator<=(const Vector2& other) const {
        return !(other < *this);
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    Vector2 next(int t, int dir) {
        return Vector2(x + t*DX[dir], y + t*DY[dir]);
    }
    
    int norm() {
        return abs(x) + abs(y);
    }
    
    int offBound() {
        if (abs(x) > L) return abs(x) - L;
        if (abs(y) > L) return abs(y) - L;
        return 0;
    }
};

vector<Vector2> head;

bool segIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p) {
    Vector2 ab = b-a, cd = d-c;
    
    if (ab.x == 0 && cd.x == 0) {
        if (a.x != c.x) return false;
        if (b < a) swap(a, b);
        if (c < d) {
            p = a;
            return (c < a && a <= d);
        } else {
            p = b;
            return (d < b && b <= c);
        }
    }
    if (ab.x == 0 && cd.y == 0) {
        p = Vector2(a.x, c.y);
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return a <= p && p <= b && c <= p && p <= d;
    }
    if (ab.y == 0 && cd.x == 0) {
        p = Vector2(c.x, a.y);
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return a <= p && p <= b && c <= p && p <= d;
    }
    if (ab.y == 0 && cd.y == 0) {
        if (a.y != c.y) return false;
        if (b < a) swap(a, b);
        if (c < d) {
            p = a;
            return (c < a && a <= d);
        } else {
            p = b;
            return (d < b && b <= c);
        }
    }
    
    assert(false);
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> N;
    head.push_back(Vector2(0, 0));
    
    dir = 0;
    ans = 0;
    bool snakeDead = false;
    
    int t;
    char rotate = 'L';
    for (int i=0; i<=N; ++i) {
        if (i == N) t = 2*L + 1;
        else cin >> t >> rotate;
        
        head.push_back(head.back().next(t, dir));
        
        int minDistance = INF;
        for (int j=0; j<i-1; ++j) {
            Vector2 p;
            if (segIntersection(head[j], head[j+1], head[i], head[i+1], p)) {
                minDistance = min(minDistance, (p - head[i]).norm());
                snakeDead = true;
            }
        }
        if (snakeDead) {
            ans += minDistance;
            break;
        }
        
        ans += t;
        int offTime = head.back().offBound();
        if (offTime != 0) {
            ans -= offTime - 1;
            snakeDead = true;
            break;
        }
        
        dir = (rotate == 'L') ? (dir+1) % 4 : (dir+3) % 4;
    }
    
    cout << ans;
    
    return 0;
}
