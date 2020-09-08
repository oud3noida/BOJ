#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int RADIX = 10;
const int DX[4] = {0, 1, 0, -1},
          DY[4] = {1, 0, -1, 0};
int ans;
set<int> visited;
queue<pair<int, int>> q;

bool inRange(int x, int y) {
    return 0 <= x && x < 3 && 0 <= y && y < 3;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int initBoard = 0;
    
    int inp;
    for (int i=0; i<9; ++i) {
        initBoard *= RADIX;
        cin >> inp;
        initBoard += inp;
    }
    
    ans = -1;
    q.push(make_pair(0, initBoard));
    visited.insert(initBoard);
    
    while (!q.empty()) {
        int curMove  = q.front().first,
            curBoard = q.front().second;
        q.pop();
        
        if (curBoard == 123456780) {
            ans = curMove;
            break;
        }
        
        int posZero;
        bool isSorted = true;
        vector<int> boardVector(9, 0);
        for (int i=0; i<9; ++i) {
            boardVector[i] = curBoard % RADIX;
            curBoard /= RADIX;
            
            if (boardVector[i] == 0) posZero = i;
            if (isSorted && i-1 >= 0) {
                if (boardVector[i-1] != 0) {
                    if (boardVector[i] >= boardVector[i-1])
                        isSorted = false;
                } else if (i-2 >= 0) {
                    if (boardVector[i] >= boardVector[i-2])
                        isSorted = false;
                }
            }
        }
        
        for (int d=0; d<4; ++d) {
            int xSwap = posZero % 3 + DX[d],
                ySwap = posZero / 3 + DY[d],
                posSwap = ySwap * 3 + xSwap;
            
            if (!inRange(xSwap, ySwap)) continue;
            
            swap(boardVector[posZero], boardVector[posSwap]);
            
            int nextBoard = 0;
            for (int i=8; i>=0; --i) {
                nextBoard *= RADIX;
                nextBoard += boardVector[i];
            }
            
            if (visited.find(nextBoard) == visited.end()) {
                q.push(make_pair(curMove+1, nextBoard));
                visited.insert(nextBoard);
            }
            
            swap(boardVector[posZero], boardVector[posSwap]);
        }
    }
    
    cout << ans;
    
    return 0;
}
