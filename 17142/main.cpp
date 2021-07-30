#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

struct State {
    Position pos;
    int cur_time;
    
    State(Position pos, int cur_time)
        : pos(pos), cur_time(cur_time) {}
};

constexpr int INF = 50*50+1;
constexpr int BLANK = 0,
              WALL = 1,
              VIRUS = 2;
constexpr int DX[4] = {0, 0, -1, 1},
              DY[4] = {-1, 1, 0, 0};
int n, num_viruses, num_quasiviruses, num_blanks;
vector<vector<int>> board;
vector<Position> quasiviruses;
vector<int> virus_index;

bool in_range(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int time_to_full() {
    queue<State> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for (int index : virus_index) {
        Position virus = quasiviruses[index];
        q.emplace(virus, 0);
        visited[virus.y][virus.x] = true;
    }
    
    int cur_time = INF;
    int num_filled_blanks = 0;
    while (!q.empty()) {
        State &cur = q.front();
        int x = cur.pos.x,
            y = cur.pos.y;
        cur_time = cur.cur_time;
        q.pop();
        
        if (board[y][x] == BLANK) ++num_filled_blanks;
        
        if (num_filled_blanks == num_blanks) {
            return cur_time;
        }
        
        for (int dir=0; dir<4; ++dir) {
            int x_next = x + DX[dir],
                y_next = y + DY[dir];
            
            if (!in_range(x_next, y_next) ||
                visited[y_next][x_next] ||
                board[y_next][x_next] == WALL) continue;
            
            q.emplace(Position(x_next, y_next), cur_time + 1);
            visited[y_next][x_next] = true;
        }
    }
    
    return INF;
}

int min_time_to_full(int cur, int prev_index) {
    if (cur == num_viruses) {
        return time_to_full();
    }
    
    int ret = INF;
    for (int index=prev_index+1; index<num_quasiviruses; ++index) {
        virus_index[cur] = index;
        ret = min(ret, min_time_to_full(cur+1, index));
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_viruses;
    
    board.assign(n, vector<int>(n, BLANK));
    num_blanks = 0;
    num_quasiviruses = 0;
    for (int y=0; y<n; ++y) {
        for (int x=0; x<n; ++x) {
            cin >> board[y][x];
            if (board[y][x] == BLANK) ++num_blanks;
            if (board[y][x] == VIRUS) {
                quasiviruses.emplace_back(x, y);
                ++num_quasiviruses;
            }
        }
    }
    
    virus_index.assign(num_viruses, -1);
    
    int ans = min_time_to_full(0, -1);
    if (ans == INF) cout << -1;
    else cout << ans;
    
    return 0;
}
