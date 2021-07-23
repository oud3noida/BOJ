#include <iostream>
#include <vector>

using namespace std;

const int BLANK = 0,
          MAX = 9;
const int DX[4] = {0, 0, -1, 1},
          DY[4] = {-1, 1, 0, 0};
int n;
vector<vector<int>> board;
vector<vector<bool>> horizontal, vertical, subsquare, domino_used;

enum DominoType {UP, DOWN, LEFT, RIGHT, SINGLE, UNDEFINED};

vector<vector<DominoType>> domino_type;

int vertical_id(char c) {
    return c - 'A';
}

int horizontal_id(char c) {
    return c - '1';
}

int subsquare_id(int x, int y) {
    return (y/3)*3 + x/3;
}

bool in_range(int x, int y) {
    return 0 <= x && x < MAX && 0 <= y && y < MAX;
}

bool is_possible_to_make_domino(int x, int y, int dir) {
    int x_adj = x + DX[dir],
        y_adj = y + DY[dir];
    
    if (!in_range(x_adj, y_adj)) return false;
    
    int a = min(board[y][x], board[y_adj][x_adj]),
        b = max(board[y][x], board[y_adj][x_adj]);
    
    return domino_type[y_adj][x_adj] == UNDEFINED &&
           !domino_used[a-1][b-1];
}

void make_domino(int x, int y, int dir) {
    const DominoType DIRECTION[4] = {DOWN, UP, RIGHT, LEFT},
                     DIRECTION_ADJ[4] = {UP, DOWN, LEFT, RIGHT};
    
    int x_adj = x + DX[dir],
        y_adj = y + DY[dir],
        a = min(board[y][x], board[y_adj][x_adj]),
        b = max(board[y][x], board[y_adj][x_adj]);
    
    domino_type[y][x] = DIRECTION[dir];
    domino_type[y_adj][x_adj] = DIRECTION_ADJ[dir];
    domino_used[a-1][b-1] = true;
}

void break_domino(int x, int y, int dir) {
    int x_adj = x + DX[dir],
        y_adj = y + DY[dir],
        a = min(board[y][x], board[y_adj][x_adj]),
        b = max(board[y][x], board[y_adj][x_adj]);
    
    domino_type[y][x] = UNDEFINED;
    domino_type[y_adj][x_adj] = UNDEFINED;
    domino_used[a-1][b-1] = false;
}

bool check_domino_for_full_sudoku(int x, int y) {
    if (x == MAX) return check_domino_for_full_sudoku(0, y+1);
    if (y == MAX) return true;
    if (domino_type[y][x] != UNDEFINED) return check_domino_for_full_sudoku(x+1, y);
    
    for (int dir=0; dir<4; ++dir) {
        if (!is_possible_to_make_domino(x, y, dir)) continue;
        
        make_domino(x, y, dir);
        bool domino_success = check_domino_for_full_sudoku(x+1, y);
        if (domino_success) return true;
        
        break_domino(x, y, dir);
    }
    
    return false;
}

bool is_possible_to_set_cell(int x, int y, int value) {
    return in_range(x, y) &&
           !horizontal[x][value-1] &&
           !vertical[y][value-1] &&
           !subsquare[subsquare_id(x, y)][value-1] &&
           board[y][x] == BLANK;
}

void set_cell(int x, int y, int value) {
    horizontal[x][value-1] = true;
    vertical[y][value-1] = true;
    subsquare[subsquare_id(x, y)][value-1] = true;
    board[y][x] = value;
}

void clear_cell(int x, int y) {
    int value = board[y][x];
    
    if (value != BLANK) {
        horizontal[x][value-1] = false;
        vertical[y][value-1] = false;
        subsquare[subsquare_id(x, y)][value-1] = false;
    }
    board[y][x] = BLANK;
}

bool fill_sudoku(int x, int y) {
    if (x == MAX) return fill_sudoku(0, y+1);
    if (y == MAX) return check_domino_for_full_sudoku(0, 0);
    if (board[y][x] != BLANK) return fill_sudoku(x+1, y);
    
    for (int i=0; i<MAX; ++i) {
        if (!is_possible_to_set_cell(x, y, i+1)) continue;
        
        set_cell(x, y, i+1);
        bool sudoku_success = fill_sudoku(x+1, y);
        if (sudoku_success) return true;
        
        clear_cell(x, y);
    }
    
    return false;
}

DominoType get_type(int x1, int y1, int x2, int y2) {
    if (y1 < y2) return UP;
    if (y1 > y2) return DOWN;
    if (x1 < x2) return RIGHT;
    if (x1 > x2) return LEFT;
    return UNDEFINED;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<vector<bool>> init(MAX, vector<bool>(MAX, false));
    
    int puzzle_no = 0;
    while (true) {
        ++puzzle_no;
        
        cin >> n;
        if (n == 0) break;
        
        board.assign(MAX, vector<int>(MAX, BLANK));
        horizontal = init;
        vertical = init;
        subsquare = init;
        domino_used = init;
        domino_type.assign(MAX, vector<DominoType>(MAX, UNDEFINED));
        
        int a, b;
        string a_pos, b_pos;
        for (int i=0; i<n; ++i) {
            cin >> a >> a_pos >> b >> b_pos;
            
            domino_used[min(a, b)-1][max(a, b)-1] = true;
            
            int x_a = horizontal_id(a_pos[1]),
                y_a = vertical_id(a_pos[0]),
                x_b = horizontal_id(b_pos[1]),
                y_b = vertical_id(b_pos[0]);
            
            set_cell(x_a, y_a, a);
            set_cell(x_b, y_b, b);
            
            domino_type[y_a][x_a] = get_type(x_a, y_a, x_b, y_b);
            domino_type[y_b][x_b] = get_type(x_b, y_b, x_a, y_a);
        }
        
        for (int i=1; i<=MAX; ++i) {
            cin >> a_pos;
            
            int x = horizontal_id(a_pos[1]),
                y = vertical_id(a_pos[0]);
            
            set_cell(x, y, i);
            
            domino_type[y][x] = SINGLE;
        }
        
        fill_sudoku(0, 0);
        
        cout << "Puzzle " << puzzle_no << '\n';
        for (int y=0; y<MAX; ++y) {
            for (int x=0; x<MAX; ++x) {
                cout << board[y][x];
            }
            cout << '\n';
        }
    }

    return 0;
}
