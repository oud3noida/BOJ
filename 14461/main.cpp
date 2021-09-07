#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

constexpr long long INF = numeric_limits<long long>::max();
constexpr int DX[16] = {-1, 1, 0, 0, -3, -2, -1, 0, 1, 2, 3, 2, 1, 0, -1, -2},
              DY[16] = {0, 0, -1, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 3, 2, 1};
int n, t_cross;
vector<vector<int>> grasses;
vector<vector<long long>> visited;

struct State {
    int x, y;
    long long t;
    
    State(int x, int y, long long t) :
        x(x), y(y), t(t) {}
    
    bool operator<(const State &other) const {
        return t > other.t;
    }
};

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> t_cross;
    
    grasses.assign(n, vector<int>(n, 0));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> grasses[y][x];
        }
    }
    
    visited.assign(n, vector<long long>(n, INF));
    
    priority_queue<State> q;
    q.emplace(0, 0, 0);
    visited[0][0] = 0;
    
    while (!q.empty()) {
        auto cur = q.top();
        int x = cur.x,
            y = cur.y;
        long long t = cur.t;
        q.pop();
                
        if (x == n-1 && y == n-1) {
            cout << t;
            break;
        }
        
        int d = (n-1 - x) + (n-1 - y);
        if (d < 3) {
            q.emplace(n-1, n-1, t + d * t_cross);
        }
        
        for (int d = 0; d < 16; d++) {
            int x_next = x + DX[d];
            int y_next = y + DY[d];
            
            if (!in_range(x_next, y_next)) continue;
            
            long long t_next = t + t_cross * 3 + grasses[y_next][x_next];
            
            if (visited[y_next][x_next] > t_next) {
                visited[y_next][x_next] = t_next;
                q.emplace(x_next, y_next, t_next);
            }
        }
    }
    
    return 0;
}
