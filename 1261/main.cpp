#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;
const int DX[4] = {0, 1, 0, -1},
          DY[4] = {1, 0, -1, 0};
int X, Y;
vector<vector<bool>> isWall;
vector<vector<int>> minBroken;

bool inRange(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

void explore(int x, int y, int curBroken) {
    if (curBroken >= minBroken[y][x]) return;
    minBroken[y][x] = curBroken;
    
    if (x == X-1 && y == Y-1) return;
    
    for (int d=0; d<4; ++d) {
        int xNext = x + DX[d],
            yNext = y + DY[d];
        if (!inRange(xNext, yNext)) continue;
        explore(xNext, yNext, curBroken + (isWall[yNext][xNext] ? 1 : 0));
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> X >> Y;
    isWall.assign(Y, vector<bool>(X, false));
    minBroken.assign(Y, vector<int>(X, INF));
    
    string row;
    for (int y=0; y<Y; ++y) {
        cin >> row;
        for (int x=0; x<X; ++x) {
            isWall[y][x] = (row[x] == '1');
        }
    }
    
    explore(0, 0, 0);
    
    cout << minBroken[Y-1][X-1];
    
    return 0;
}
