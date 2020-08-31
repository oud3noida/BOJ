#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int BLANK = -1;
int X, Y, x, y, xDir, yDir, score;
vector<string> board;
vector<int> parent;

int find(int x) {
    if (x == BLANK) return BLANK;
    if (x != parent[x]) return parent[x] = find(parent[x]);
    return x;
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    
    if (a == b) return;
    else if (b == BLANK) parent[a] = b;
    else parent[b] = a;
}

int coord2id(int x, int y) {
    return x + y*X;
}

void goVertically() {
    y += yDir;
    if (board[y][x] == 'B') {
        int curBlock = find(coord2id((x-1)/2, (y-1)/2));
        if (curBlock != BLANK) {
            merge(curBlock, BLANK);
            ++score;
        }
    }
    if (y == 0) yDir *= -1;
}

void goHorizontally() {
    x += xDir;
    if (board[y][x] == 'B') {
        int curBlock = find(coord2id((x-1)/2, (y-1)/2));
        if (curBlock != BLANK) {
            merge(curBlock, BLANK);
            ++score;
        }
    }
    if (x == 0 || x == 2*X) xDir *= -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> X >> Y;
    for (int i=0; i<X*Y; ++i) parent.push_back(i);
    
    double k;
    cin >> k;
    x = 2*k; y = 2*Y;
    xDir = -1; yDir = -1;
    
    board.assign(2*Y+1, "");
    for (int j=0; j<=2*Y; ++j) cin >> board[j];
    
    for (int j=0; j<=2*Y; ++j) {
        for (int i=0; i<=2*X; ++i) {
            if (board[j][i] == 'O') {
                merge(coord2id((i-1)/2, (j-1)/2), BLANK);
            } else if (board[j][i] == '.') {
                if (i != 0 && i != 2*X && j != 0 && j != 2*Y) {
                    if (i % 2 == 1) merge(coord2id((i-1)/2, j/2-1), coord2id((i-1)/2, j/2));
                    else merge(coord2id(i/2-1, (j-1)/2), coord2id(i/2, (j-1)/2));
                }
            }
        }
    }
    
    score = 0;
    do {
        goVertically();
        goHorizontally();
        goHorizontally();
        goVertically();
    } while (y != 2*Y);
    
    cout << score;
    
    return 0;
}
