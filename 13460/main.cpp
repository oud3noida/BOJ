#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

int n, m, numTilt;
char board[10][10];
vector<int> horWall[10], verWall[10];
pair<int, int> red, blue, hole;
bool clear, fail;

int findPrevWall(int cur, vector<int>& line) {
    /*
        Finds the nearest wall (index from vector 'line', technically)
        on the left(horizontal)/upper(vertical) side of the position 'cur'.
    */
    int left = 0, right = line.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (line[mid] < cur) left = mid+1;
        else right = mid;
    }
    return left-1;
}

bool swap(pair<int, int> to, pair<int, int>& from) {
    /*
        If 'to' and 'from' are equal, returns false.
        Otherwise, swaps 'to' and 'from', overwrites 'from' with 'to',
                   and returns true.
    */
    int x0 = from.first, y0 = from.second,
        x1 = to.first,   y1 = to.second;
    
    if (x0 == x1 && y0 == y1) return false;
    
    char tmp = board[y0][x0];
    board[y0][x0] = board[y1][x1];
    board[y1][x1] = tmp;
    
    from = make_pair(x1, y1);
    return true;
}

bool move(pair<int, int>& pos, int dir) {
    int nextIdx;
    int  x = pos.first,   y = pos.second,
        xh = hole.first, yh = hole.second;
    char marble0 = board[y][x],
         marble1 = (marble0 == 'R') ? 'B' : 'R';
    
    switch (dir) {
        case 0: // Up
        // Find the cell to which the marble will move
        nextIdx = verWall[x][findPrevWall(y, verWall[x])] + 1;
        
        // If the marble is to fall into the hole:
        //     if the marble is red, 'clear' is set;
        //     if the marble is blue, 'fail' is set
        if (x == xh && y > yh && nextIdx == verWall[xh][findPrevWall(yh, verWall[xh])] + 1) {
            if (marble0 == 'R') clear = true;
            else if (marble0 == 'B') fail = true;
            board[y][x] = '.';
            return true;
        }
        
        // Do not allow multiple marbles in one cell
        if (board[nextIdx][x] == marble1) nextIdx++;
        
        return swap(make_pair(x, nextIdx), pos);
        
        // -------------- For the below cases, refer to the comments above --------------
        
        case 1: // Down
        nextIdx = verWall[x][findPrevWall(y, verWall[x])+1] - 1;
        if (x == xh && y < yh && nextIdx == verWall[xh][findPrevWall(yh, verWall[xh])+1] - 1) {
            if (marble0 == 'R') clear = true;
            else if (marble0 == 'B') fail = true;
            board[y][x] = '.';
            return true;
        }
        if (board[nextIdx][x] == marble1) nextIdx--;
        return swap(make_pair(x, nextIdx), pos);
        
        case 2: // Left
        nextIdx = horWall[y][findPrevWall(x, horWall[y])] + 1;
        if (y == yh && x > xh && nextIdx == horWall[yh][findPrevWall(xh, horWall[yh])] + 1) {
            if (marble0 == 'R') clear = true;
            else if (marble0 == 'B') fail = true;
            board[y][x] = '.';
            return true;
        }
        if (board[y][nextIdx] == marble1) nextIdx++;
        return swap(make_pair(nextIdx, y), pos);
        
        case 3: // Right
        nextIdx = horWall[y][findPrevWall(x, horWall[y])+1] - 1;
        if (y == yh && x < xh && nextIdx == horWall[yh][findPrevWall(xh, horWall[yh])+1] - 1) {
            if (marble0 == 'R') clear = true;
            else if (marble0 == 'B') fail = true;
            board[y][x] = '.';
            return true;
        }
        if (board[y][nextIdx] == marble1) nextIdx--;
        return swap(make_pair(nextIdx, y), pos);
        
        // ------------------------------------------------------------------------------
    }
    
    // ERROR
    assert(true);
    return false;
}

bool compMarble(pair<int, int>& pos1, pair<int, int>& pos2, int dir) {
    int x1 = pos1.first, y1 = pos1.second,
        x2 = pos2.first, y2 = pos2.second;
    switch (dir) {
        case 0: return y1 < y2;
        case 1: return y1 > y2;
        case 2: return x1 < x2;
        case 3: return x1 > x2;
    }
    
    // ERROR
    assert(true);
    return false;
}

void tiltBoard(int cur) {
    if (cur > 10 || cur > numTilt) return;
    
    // Save current state
    char save[10][10];
    for (int y=0; y<n; y++) {
        for (int x=0; x<m; x++) {
            save[y][x] = board[y][x];
        }
    }
    pair<int, int> redSave = red, blueSave = blue;
    
    bool move0, move1;
    for (int dir=0; dir<4; dir++) {
        if (compMarble(red, blue, dir)) {
            move0 = move(red, dir);
            move1 = move(blue, dir);
        } else {
            move0 = move(blue, dir);
            move1 = move(red, dir);
        }
        
        // If only the red marble fell into the hole, update numTilt and escape
        // If no marbles fell into the hole, continue the game (recursively)
        // If the blue marble fell into the hole, reset 'clear' and 'fail'
        if (clear && !fail) {
            numTilt = min(numTilt, cur);
            clear = false;
            return;
        } else if (!fail && (move0 || move1)) {
            tiltBoard(cur+1);
        } else {
            clear = false;
            fail = false;
        }
        
        // Return to the initial state
        for (int y=0; y<n; y++) {
            for (int x=0; x<m; x++) {
                board[y][x] = save[y][x];
            }
        }
        red = redSave;
        blue = blueSave;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    
    string cells;
    for (int y=0; y<n; y++) {
        cin >> cells;
        for (int x=0; x<m; x++) {
            if (cells[x] == '#') {
                horWall[y].push_back(x);
                verWall[x].push_back(y);
            } else if (cells[x] == 'R') red = make_pair(x, y);
            else if (cells[x] == 'B') blue = make_pair(x, y);
            else if (cells[x] == 'O') hole = make_pair(x, y);
            board[y][x] = cells[x];
        }
    }
    
    numTilt = 99;
    tiltBoard(1);
    
    cout << ((numTilt <= 10) ? numTilt : -1);
    
    return 0;
}
