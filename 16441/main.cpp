#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int DX[4] = {-1, 1, 0, 0},
              DY[4] = {0, 0, -1, 1};
constexpr char PLAIN = '.',
               MOUNTAIN = '#',
               ICE = '+',
               WOLF = 'W',
               PIG = 'P';
int x_max, y_max;
vector<string> board;
vector<vector<bool>> wolf_visited;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    wolf_visited.assign(y_max, vector<bool>(x_max, false));
    queue<pair<int, int>> q;
    
    string row;
    for (int y = 0; y < y_max; y++) {
        cin >> row;
        board.push_back(row);
        
        for (int x = 0; x < x_max; x++) {
            if (board[y][x] == WOLF) {
                wolf_visited[y][x] = true;
                q.emplace(x, y);
            }
        }
    }
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int x_next = x + DX[d];
            int y_next = y + DY[d];
            
            if (board[y_next][x_next] == MOUNTAIN) continue;
            
            while (board[y_next][x_next] == ICE) {
                if (board[y_next + DY[d]][x_next + DX[d]] == MOUNTAIN) {
                    break;
                }
                
                x_next += DX[d];
                y_next += DY[d];
            }
            
            if (wolf_visited[y_next][x_next]) continue;
            
            wolf_visited[y_next][x_next] = true;
            q.emplace(x_next, y_next);
        }
    }
    
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            if (board[y][x] == PLAIN && !wolf_visited[y][x]) {
                cout << PIG;
            } else {
                cout << board[y][x];
            }
        }
        cout << '\n';
    }
    
    return 0;
}
