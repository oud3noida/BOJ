#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pails {
    int x, y, k;
    
    Pails(int x, int y, int k) : x(x), y(y), k(k) {}
};

int x_max, y_max, k_max, milk, min_error;
vector<vector<bool>> visited;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> x_max >> y_max >> k_max >> milk;
    
    visited.assign(x_max+1, vector<bool>(y_max+1, false));
    
    queue<Pails> q;
    q.emplace(0, 0, 0);
    visited[0][0] = true;
    
    min_error = 200;
    while (!q.empty()) {
        auto cur = q.front();
        int x = cur.x,
            y = cur.y,
            k = cur.k;
        q.pop();
        
        min_error = min(min_error, abs(x+y - milk));
        
        if (k == k_max) continue;
        
        if (x < x_max) {
            if (!visited[x_max][y]) {
                visited[x_max][y] = true;
                q.emplace(x_max, y, k + 1);
            }
            
            if (y > 0) {
                int d = min(y, x_max - x);
                if (!visited[x + d][y - d]) {
                    visited[x + d][y - d] = true;
                    q.emplace(x + d, y - d, k + 1);
                }
            }
        }
        
        if (y < y_max) {
            if (!visited[x][y_max]) {
                visited[x][y_max] = true;
                q.emplace(x, y_max, k + 1);
            }
            
            if (x > 0) {
                int d = min(x, y_max - y);
                if (!visited[x - d][y + d]) {
                    visited[x - d][y + d] = true;
                    q.emplace(x - d, y + d, k + 1);
                }
            }
        }
        
        if (!visited[x][0]) {
            visited[x][0] = true;
            q.emplace(x, 0, k + 1);
        }
        
        if (!visited[0][y]) {
            visited[0][y] = true;
            q.emplace(0, y, k + 1);
        }
    }
    
    cout << min_error;
    
    return 0;
}
