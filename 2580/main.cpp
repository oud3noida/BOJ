#include <iostream>
#include <string.h>

using namespace std;

int board[9][9];
int hor[9], ver[9], sub[9];

bool getDup(int x, int y, int n) {
    return (hor[y] & (1 << n)) ||
           (ver[x] & (1 << n)) ||
           (sub[(y/3)*3 + x/3] & (1 << n));
}

void setDup(int x, int y, int n) {
    hor[y] |= (1 << n);
    ver[x] |= (1 << n);
    sub[(y/3)*3 + x/3] |= (1 << n);
}

void resetDup(int x, int y, int n) {
    hor[y] &= ~(1 << n);
    ver[x] &= ~(1 << n);
    sub[(y/3)*3 + x/3] &= ~(1 << n);
}

bool sudoku(int x, int y) {
    if (x == 9) return sudoku(0, y+1);  // End of the line
    if (y == 9) return true;            // End of the whole board
    if (board[y][x] != 0) return sudoku(x+1, y);
    
    for (int i=1; i<=9; i++) {
        if (getDup(x, y, i)) continue;
        setDup(x, y, i);
        board[y][x] = i;
        if (sudoku(x+1, y)) return true;
        resetDup(x, y, i);
        board[y][x] = 0;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    memset(hor, 0, sizeof(hor));
    memset(ver, 0, sizeof(ver));
    memset(sub, 0, sizeof(sub));
    
    for (int y=0; y<9; y++) {
        for (int x=0; x<9; x++) {
            cin >> board[y][x];
            if (board[y][x] != 0) setDup(x, y, board[y][x]);
        }
    }
    
    sudoku(0, 0);
    
    for (int y=0; y<9; y++) {
        for (int x=0; x<9; x++) {
            cout << board[y][x] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
