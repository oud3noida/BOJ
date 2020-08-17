#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int DX[4] = {-1, 0, 1, 0},
          DY[4] = {0, -1, 0, 1};
int X, Y, roomNum, maxMerged;
vector<vector<int>> cells;
vector<vector<bool>> visited;
vector<vector<bool>> adj;
vector<int> roomArea;

bool inRange(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

int traverseCell(int x, int y) {
    if (!inRange(x, y) || visited[y][x]) return 0;
    visited[y][x] = true;
    
    int ret = 1;
    for (int dir=0; dir<4; ++dir)
        if (!(cells[y][x] & (1<<dir)))
            ret += traverseCell(x+DX[dir], y+DY[dir]);
    
    cells[y][x] = roomNum;
    return ret;
}

void makeGraph(int x, int y) {
    visited[y][x] = true;
    int cur = cells[y][x];
    
    if (inRange(x+1, y) && !visited[y][x+1]) {
        int next = cells[y][x+1];
        if (cur != next) {
            adj[cur][next] = true;
            adj[next][cur] = true;
        }
        makeGraph(x+1, y);
    }
    if (inRange(x, y+1) && !visited[y+1][x]) {
        int next = cells[y+1][x];
        if (cur != next) {
            adj[cur][next] = true;
            adj[next][cur] = true;
        }
        makeGraph(x, y+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> X >> Y;
    cells.assign(Y, vector<int>(X, 0));
    visited.assign(Y, vector<bool>(X, false));
    roomNum = 0;
    
    for (int y=0; y<Y; ++y)
        for (int x=0; x<X; ++x)
            cin >> cells[y][x];
    
    for (int y=0; y<Y; ++y) {
        for (int x=0; x<X; ++x) {
            if (visited[y][x]) continue;
            roomArea.push_back(traverseCell(x, y));
            ++roomNum;
        }
    }
    
    visited.assign(Y, vector<bool>(X, false));
    adj.assign(roomNum, vector<bool>(roomNum, false));
    makeGraph(0, 0);
    
    maxMerged = 0;
    for (int i=0; i<roomNum; ++i)
        for (int j=0; j<roomNum; ++j)
            if (adj[i][j])
                maxMerged = max(maxMerged, roomArea[i] + roomArea[j]);
    
    cout << roomNum << "\n";
    cout << *max_element(roomArea.begin(), roomArea.end()) << "\n";
    cout << maxMerged;
    
    return 0;
}
