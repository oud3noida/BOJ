#include <iostream>
#include <vector>

using namespace std;

const int DX[4] = {0, 1, 0, -1},    // (north, east, south, west)
          DY[4] = {-1, 0, 1, 0};    // (north, east, south, west)
const int FRONT = 0, LEFT = 1, BACK = 2, RIGHT = 3,
          CLEAR = -1, BLANK = 0, WALL = 1;
int X, Y, x, y, ans;
int curDir[4];
vector<vector<int>> board;

int exploreCell(int dir) {
    int _x = x + DX[curDir[dir]],
        _y = y + DY[curDir[dir]];
    return board[_y][_x];
}

void turnLeft(int n) {
    for (int d=0; d<4; ++d) curDir[d] = (4+curDir[d]-n) % 4;
}

void move(int dir) {
    x += DX[curDir[dir]];
    y += DY[curDir[dir]];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int initDir;
    cin >> Y >> X >> y >> x >> initDir;
    for (int d=0; d<4; ++d) curDir[d] = (4+initDir--) % 4;
    
    board.assign(Y, vector<int>(X, BLANK));
    for (int _y=0; _y<Y; ++_y)
        for (int _x=0; _x<X; ++_x)
            cin >> board[_y][_x];
    
    ans = 0;
    bool done = false;
    while (!done) {
        
        if (board[y][x] == BLANK) {
            board[y][x] = CLEAR;
            ++ans;
        }
        
        bool moveBackward = true;
        for (int d=1; d<5; ++d) {
            if (exploreCell(d%4) != BLANK) continue;
            turnLeft(d);
            move(FRONT);
            moveBackward = false;
            break;
        }
        if (moveBackward) {
            if (exploreCell(BACK) == WALL) done = true;
            else move(BACK);
        }
    }
    
    cout << ans;
    
    return 0;
}
