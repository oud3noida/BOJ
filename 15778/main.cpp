#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Position {
    int x, y;
    bool playing;
    Position(int x=30, int y=30, bool playing=false)
    : x(x), y(y), playing(playing) {}
    
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y, playing || other.playing);
    }
    
    bool operator==(const Position& other) const {
        return (x == other.x) && (y == other.y) && (playing == other.playing);
    }
};

const int PIECE_X[4] = {0, 0, 1, 1},
          PIECE_Y[4] = {0, 1, 0, 1};
const Position POS_START = Position(),
               POS_END = Position(30, 30, true),
               POS_OUT = Position(-1, -1);
const vector<int> TEAM_UPPER = {0, 1, 2, 3},
                  TEAM_LOWER = {4, 5, 6, 7};
int N;
int parent[8];
Position pos[8];
char board[32][33] = {
"..----..----..----..----..----..",     // (0,0)  (0,6)  (0,12)  (0,18)  (0,24)  (0,30)
"..    ..    ..    ..    ..    ..",
"| \\                          / |",
"|  \\                        /  |",
"|   \\                      /   |",
"|    ..                  ..    |",     //     (5,5)                        (5,25)
"..   ..                  ..   ..",     // (6,0)                                 (6,30)
"..     \\                /     ..",
"|       \\              /       |",
"|        \\            /        |",
"|         ..        ..         |",     //           (10,10)        (10,20)
"|         ..        ..         |",
"..          \\      /          ..",    // (12,0)                                (12,30)
"..           \\    /           ..",
"|             \\  /             |",
"|              ..              |",     //                  (15,15)
"|              ..              |",
"|             /  \\             |",
"..           /    \\           ..",    // (18,0)                                (18,30)
"..          /      \\          ..",
"|         ..        ..         |",     //           (20,10)        (20,20)
"|         ..        ..         |",
"|        /            \\        |",
"|       /              \\       |",
"..     /                \\     ..",    // (24,0)                                (24,30)
"..   ..                  ..   ..",     //     (25,5)                       (25,25)
"|    ..                  ..    |",
"|   /                      \\   |",
"|  /                        \\  |",
"| /                          \\ |",
"..    ..    ..    ..    ..    ..",     // (30,0) (30,6) (30,12) (30,18) (30,24) (30,30)
"..----..----..----..----..----.."};

int find(int i) {
    if (i != parent[i]) return parent[i] = find(parent[i]);
    return i;
}

void merge(int a, int b) {
    parent[find(a)] = find(b);
}

char num2piece(int n) {
    // 0 1 2 3 4 5 6 7
    // A B C D a b c d
    if (0 <= n && n < 4) return 'A' + n;
    if (4 <= n && n < 8) return 'a' + (n-4);
    
    assert(false);
    return ' ';
}

int piece2num(char c) {
    // A B C D a b c d
    // 0 1 2 3 4 5 6 7
    if ('A' <= c && c <= 'D') return c - 'A';
    if ('a' <= c && c <= 'd') return c - 'a' + 4;
    
    assert(false);
    return -1;
}

int yuts2num(string yuts) {
    assert(yuts.length() == 4);
    
    int ret = 0;
    for (char c : yuts) {
        if (c == 'F') ++ret;
    }
    return (ret != 0) ? ret : 5;
}

bool inRange(Position &p) {
    return 0 <= p.x && p.x <= 30 && 0 <= p.y && p.y <= 30;
}

vector<int> ally(int id) {
    return (id/4 == 0) ? TEAM_UPPER : TEAM_LOWER;
}

vector<int> enemy(int id) {
    return (id/4 == 0) ? TEAM_LOWER : TEAM_UPPER;
}

void movePiece(char piece, int times) {
    int pieceID = find(piece2num(piece));
    Position &curPos = pos[pieceID];
    
    if (!curPos.playing) {
        curPos.playing = true;
        curPos = curPos + Position(-6, 0);
        --times;
    }
    
    int shortcut = 0;
    if (curPos.x - curPos.y == 0)
        shortcut = 2;
    else if (curPos.x + curPos.y == 30)
        shortcut = 1;
    
    while (inRange(curPos) && times-- > 0) {
        if (curPos == POS_END) // END
            curPos = POS_OUT;
        else if (curPos.x == 30) // NAL-DO ~ NAL-YUT
            curPos = curPos + Position(0, 6);
        else if (shortcut == 1) // AP-MO-DO ~ SOK-MO
            curPos = curPos + Position(5, -5);
        else if (shortcut == 2) // DWIT-MO-DO ~ AN-JJEO
            curPos = curPos + Position(5, 5);
        else if (curPos.y == 0) // JJEOL-DO ~ JJEOL-YUT
            curPos = curPos + Position(6, 0);
        else if (curPos.x == 0) // DWIT-DO ~ DWIT-YUT
            curPos = curPos + Position(0, -6);
        else if (curPos.y == 30) // DO ~ YUT
            curPos = curPos + Position(-6, 0);
    }
    
    // Union with ally pieces
    for (int allyID : ally(pieceID)) {
        if (pos[find(allyID)] == curPos)
            merge(allyID, pieceID);
    }
}

void printBoard() {
    for (int i=0; i<8; ++i) {
        Position iPos = pos[find(i)];
        if (iPos == POS_START || iPos == POS_OUT) continue;
        board[iPos.x + PIECE_X[i%4]][iPos.y + PIECE_Y[i%4]] = num2piece(i);
    }
    
    for (auto &row : board) cout << row << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    for (int i=0; i<8; ++i) {
        parent[i] = i;
        pos[i] = Position();
    }
    
    cin >> N;
    
    char piece;
    string yuts;
    for (int i=0; i<N; ++i) {
        cin >> piece >> yuts;
        movePiece(piece, yuts2num(yuts));
    }
    
    printBoard();
    
    return 0;
}
