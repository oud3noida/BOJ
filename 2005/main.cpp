#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vector2 {
    double x, y;
    
    Vector2(double x, double y) : x(x), y(y) {}
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
};

struct Segment {
    Vector2 top, bottom;
    
    Segment(Vector2 top, Vector2 bottom)
        : top(top), bottom(bottom) {}
    
    Segment(double h, double r, double R)
        : top(Vector2(R, h)), bottom(Vector2(r, 0)) {}
    
    Segment lifted(double y) {
        return Segment(top + Vector2(0, y), bottom + Vector2(0, y));
    }
    
    double gradient() {
        return (top.y - bottom.y) / (top.x - bottom.x);
    }
    
    double y(double x) {
        if (x < bottom.x || top.x < x) return -1;
        return gradient() * (x - bottom.x) + bottom.y;
    }
};

constexpr int INF = 99999;
int n;
vector<Segment> bowls;

double height_increment_when_piled(Segment upper, Segment lower) {
    if (lower.top.x <= upper.bottom.x) return lower.top.y;
    
    double ret;
    if (lower.gradient() <= upper.gradient()) {
        ret = lower.y(upper.bottom.x);
    } else if (lower.bottom.x <= upper.top.x && upper.top.x <= lower.top.x) {
        double contact = lower.y(upper.top.x);
        if (contact < 0) return lower.bottom.y;
        ret = contact - (upper.top.y - upper.bottom.y);
    } else {
        double contact = upper.y(lower.top.x);
        if (contact < 0) return lower.bottom.y;
        ret = lower.top.y - contact;
    }
    
    return max(ret, lower.bottom.y);
}

int minimum_height(vector<int> &piling_order) {
    vector<Segment> piled_bowls;
    
    double ret = 0;
    for (int bowl_index : piling_order) {
        auto &upper = bowls[bowl_index];
        double dh = 0;
        for (auto &lower : piled_bowls) {
            dh = max(dh, height_increment_when_piled(upper, lower));
        }
        piled_bowls.push_back(upper.lifted(dh));
        ret = max(ret, piled_bowls.back().top.y);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int h, r, R;
    vector<int> piling_order;
    for (int i=0; i<n; ++i) {
        cin >> h >> r >> R;
        bowls.emplace_back(h, r, R);
        piling_order.push_back(i);
    }
    
    int ans = INF;
    do {
        ans = min(ans, minimum_height(piling_order));
    } while (next_permutation(piling_order.begin(), piling_order.end()));
    
    cout << ans;
    
    return 0;
}
