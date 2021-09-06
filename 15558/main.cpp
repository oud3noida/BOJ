#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int i, side, t;
    
    State(int i, int side, int t) : i(i), side(side), t(t) {}
};

int n, jump;
vector<string> board;
vector<vector<bool>> visited;
queue<State> q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> jump;
    
    board.assign(2, string());
    cin >> board[0] >> board[1];
    
    visited.assign(n, vector<bool>(2, false));
    q.emplace(0, 0, 0);
    visited[0][0] = true;
    
    while (!q.empty()) {
        auto cur = q.front();
        int i = cur.i,
            side = cur.side,
            t = cur.t;
        q.pop();
        
        if (i + jump >= n) {
            cout << 1;
            return 0;
        }
        
        if (board[side][i + 1] == '1' && !visited[i + 1][side]) {
            visited[i + 1][side] = true;
            q.emplace(i + 1, side, t + 1);
        }
        
        if (i - 1 >= t + 1 &&
            board[side][i - 1] == '1' && !visited[i - 1][side]) {
            visited[i - 1][side] = true;
            q.emplace(i - 1, side, t + 1);
        }
        
        int other_side = (side + 1) % 2;
        if (board[other_side][i + jump] == '1' && !visited[i + jump][other_side]) {
            visited[i + jump][other_side] = true;
            q.emplace(i + jump, other_side, t + 1);
        }
    }
    
    cout << 0;
    return 0;
}
