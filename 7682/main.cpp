#include <iostream>
#include <vector>

using namespace std;

string board;

bool isValid() {
    int numO = 0, numX = 0;
    bool winO = false, winX = false;
    // 0~2: row 1~3; 3~5: column 1~3; 6: diagonal \; 7: diagonal /
    vector<int> bingo = vector<int>(8, 0);
    
    for (int i=0; i<9; ++i) {
        if (board[i] == 'O') ++numO;
        else if (board[i] == 'X') ++numX;
        else continue;
        
        // Row bingo
        for (int j=0; j<3; ++j) {
            if (i < 3*j || 3*j+3 <= i) continue;
            if (board[i] == 'O') ++bingo[j];
            else --bingo[j];
        }
        
        // Column bingo
        if (board[i] == 'O') ++bingo[i%3+3];
        else --bingo[i%3+3];
        
        // Diagonal bingo
        if (i%4 == 0) {
            if (board[i] == 'O') ++bingo[6];
            else --bingo[6];
        }
        if (i%8 != 0 && i%2 == 0) {
            if (board[i] == 'O') ++bingo[7];
            else --bingo[7];
        }
    }
    
    for (int i=0; i<8; ++i) {
        if (bingo[i] == 3) winO = true;
        else if (bingo[i] == -3) winX = true;
    }
    
    if (winO && winX) return false;
    if (winO) return (numO == numX);
    if (winX || numO + numX == 9) return (numX == numO + 1);
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    while (true) {
        cin >> board;
        if (board == "end") break;
        cout << (isValid() ? "valid\n" : "invalid\n");
    }
    
    return 0;
}
