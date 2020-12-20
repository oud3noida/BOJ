#include <iostream>
#include <vector>

using namespace std;

const int DX[3] = {-1, 1, 0},
          DY[3] = {0, 0, 1};
int N;
int xHeart, yHeart;
int lenLeftArm, lenRightArm, lenWaist, lenLeftLeg, lenRightLeg;
vector<string> board;

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

int lenLimb(int x, int y, int dir) {
    // DIR = LEFT : 0, RIGHT : 1, DOWN : 2
    int ret = 0;
    
    while (inRange(x, y) && board[y][x] == '*') {
        ++ret;
        x += DX[dir];
        y += DY[dir];
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    xHeart = -1;
    
    string row;
    for (int i=0; i<N; ++i) {
        cin >> row;
        board.push_back(row);
        
        if (xHeart != -1) continue;
        
        for (int j=0; j<N; ++j) {
            if (board[i][j] == '_') continue;
            xHeart = j;
            yHeart = i+1;
            break;
        }
    }
    
    cout << yHeart+1 << " " << xHeart+1 << "\n";
    
    lenLeftArm = lenLimb(xHeart-1, yHeart, 0);
    lenRightArm = lenLimb(xHeart+1, yHeart, 1);
    lenWaist = lenLimb(xHeart, yHeart+1, 2);
    lenLeftLeg = lenLimb(xHeart-1, yHeart+lenWaist+1, 2);
    lenRightLeg = lenLimb(xHeart+1, yHeart+lenWaist+1, 2);
    
    cout << lenLeftArm << " " << lenRightArm << " " << lenWaist << " "
         << lenLeftLeg << " " << lenRightLeg;
    
    return 0;
}