#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

const int DX[5] = {0, 1, -1, 0, 0},    // (center, east, west, north, south)
          DY[5] = {0, 0, 0, -1, 1};    // (center, east, west, north, south)
enum Face {UP, NORTH, EAST, WEST, SOUTH, DOWN};
int X, Y, x, y, query;
int dice[6];
vector<vector<int>> board;

bool inRange(int x, int y) {
    return (0 <= x) && (x < X) && (0 <= y) && (y < Y);
}

void swapFour(int &x1, int &x2, int &x3, int &x4) {
    int tmp = x1;
    x1 = x2;
    x2 = x3;
    x3 = x4;
    x4 = tmp;
}

void rollDice(int dir) {
    if (dir == 1) swapFour(dice[EAST], dice[UP], dice[WEST], dice[DOWN]);
    if (dir == 2) swapFour(dice[WEST], dice[UP], dice[EAST], dice[DOWN]);
    if (dir == 3) swapFour(dice[NORTH], dice[UP], dice[SOUTH], dice[DOWN]);
    if (dir == 4) swapFour(dice[SOUTH], dice[UP], dice[NORTH], dice[DOWN]);
}

bool moveDice(int dir) {
    assert(1 <= dir && dir <= 4);
    
    if (!inRange(x + DX[dir], y + DY[dir])) return false;
    
    x += DX[dir]; y += DY[dir];
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X >> y >> x >> query;
    
    board.assign(Y, vector<int>(X, 0));
    for (int h=0; h<Y; ++h) {
        for (int v=0; v<X; ++v) {
            cin >> board[h][v];
        }
    }
    
    int d;
    for (int i=0; i<query; ++i) {
        cin >> d;
        if (!moveDice(d)) continue;
        rollDice(d);
        
        if (board[y][x] == 0) {
            board[y][x] = dice[DOWN];
        } else {
            dice[DOWN] = board[y][x];
            board[y][x] = 0;
        }
        cout << dice[UP] << "\n";
    }
    
    return 0;
}
