#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DX[4] = {-1, 0, 1, 0},
          DY[4] = {0, -1, 0, 1};
int X, Y, xStart, yStart;
vector<string> board;
vector<vector<bool>> visited;
vector<bool> unlock;
queue<pair<int, int>> q;
vector<pair<int, int>> record;

bool inRange(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

bool isKey(char c) {
    return 'a' <= c && c <= 'z';
}

bool isLock(char c) {
    return 'A' <= c && c <= 'Z';
}

int char2num(char c) {
    return isKey(c) ? c - 'a' : c - 'A';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X;
    
    visited.assign(Y, vector<bool>(X, false));
    unlock.assign(26, false);
    
    string row;
    for (int y=0; y<Y; ++y) {
        cin >> row;
        board.push_back(row);
        
        if (q.size() != 0) continue;
        for (int x=0; x<X; ++x) {
            if (board[y][x] == '@'){
                q.push(make_pair(x, y));
                visited[y][x] = true;
                break;
            }
        }
    }
    
    while (!q.empty()) {
        auto cur = q.front();
        int xCur = cur.first,
            yCur = cur.second;
        char cell = board[yCur][xCur];
        q.pop();
        
        if (isLock(cell) && !unlock[char2num(cell)]) {
            q.push(cur);
            continue;
        }
        
        record.push_back(cur);
        
        if (isKey(cell)) unlock[char2num(cell)] = true;
        else if (cell == '!') break;
        
        for (int d=0; d<4; ++d) {
            int xNext = xCur + DX[d],
                yNext = yCur + DY[d];
            if (!inRange(xNext, yNext) || visited[yNext][xNext]) continue;
            if (board[yNext][xNext] == '#') continue;
            q.push(make_pair(xNext, yNext));
            visited[yNext][xNext] = true;
        }
    }
    
    cout << record.size() << "\n";
    for (auto r : record) {
        cout << r.second+1 << " " << r.first+1 << "\n";
    }
    
    return 0;
}