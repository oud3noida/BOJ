#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Position {
    int x, y;
    Position(int x=30, int y=30) : x(x), y(y) {}
    
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }
    
    bool operator==(const Position& other) const {
        return (x == other.x) && (y == other.y);
    }
};

const int PIECE_X[4] = {0, 0, 1, 1},
          PIECE_Y[4] = {0, 1, 0, 1};
const Position POS_START = Position();
int N;
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

void changePiecePos(Position &p, Position delta, int times) {
    while (inRange(p) && times-- > 0) {
        p = p + delta;
    }
}

void movePiece(char piece, int times) {
    int pieceID = piece2num(piece);
    changePiecePos(pos[pieceID], Position(-6, 0), times);
}

void printBoard() {
    for (int i=0; i<8; ++i) {
        if (pos[i] == POS_START) continue;
        board[pos[i].x + PIECE_X[i%4]][pos[i].y + PIECE_Y[i%4]] = num2piece(i);
    }
    
    for (auto &row : board) cout << row << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    for (int i=0; i<8; ++i) pos[i] = Position();
    
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
