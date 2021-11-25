#include <iostream>
#include <vector>
#include <set>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
int x_max, y_max;
vector<int> cnt;
vector<vector<int>> board, shape_index;
vector<vector<bool>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

void set_index(int x, int y, int i) {
    visited[y][x] = true;
    shape_index[y][x] = i;
    cnt[i]++;
    
    for (int d = 0; d < 4; d++) {
        int x_next = x + DX[d],
            y_next = y + DY[d];
        
        if (!in_range(x_next, y_next) ||
            visited[y_next][x_next] ||
            board[y_next][x_next] == 0) {
            continue;
        }
        
        set_index(x_next, y_next, i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, vector<int>(x_max, 0));
    shape_index.assign(y_max, vector<int>(x_max, -1));
    visited.assign(y_max, vector<bool>(x_max, false));
    
    // Input board
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            cin >> board[y][x];
        }
    }
    
    // Set index to all shapes
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            if (visited[y][x] || board[y][x] == 0) {
                continue;
            }
            
            cnt.push_back(0);
            set_index(x, y, cnt.size() - 1);
        }
    }
    
    // Try connecting shapes
    int ans = 0;
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            if (board[y][x] == 0) {
                set<int> adj;
                int cur_ans = 1;
                
                for (int d = 0; d < 4; d++) {
                    int x_next = x + DX[d],
                        y_next = y + DY[d];
                    
                    if (in_range(x_next, y_next) && board[y_next][x_next] == 1) {
                        adj.insert(shape_index[y_next][x_next]);
                    }
                }
                
                for (int i : adj) {
                    cur_ans += cnt[i];
                }
                
                ans = max(ans, cur_ans);
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
