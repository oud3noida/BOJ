#include <iostream>
#include <vector>

using namespace std;

struct Position {
    int x, y;
    
    Position(int x, int y) : x(x), y(y) {}
};

int x_max, y_max, num_shapes;
vector<vector<int>> rectangle_board, diamond_board;

bool in_range(int x, int y) {
    return 0 <= x && x <= x_max && 0 <= y && y <= y_max;
}

vector<pair<Position, int>> rectangle_markers(int px, int py, int qx, int qy) {
    vector<pair<Position, int>> ret;
    
    ret.emplace_back(Position(px,     py),     1);
    ret.emplace_back(Position(qx + 1, py),     -1);
    ret.emplace_back(Position(px,     qy + 1), -1);
    ret.emplace_back(Position(qx + 1, qy + 1), 1);
    
    return ret;
}

vector<pair<Position, int>> diamond_markers(int px, int py, int r) {
    vector<pair<Position, int>> ret;
    
    ret.emplace_back(Position(px - r,     py),         1);
    ret.emplace_back(Position(px - r + 1, py),         1);
    ret.emplace_back(Position(px + r + 1, py),         1);
    ret.emplace_back(Position(px + r + 2, py),         1);
    ret.emplace_back(Position(px + 1,     py - r - 1), -1);
    ret.emplace_back(Position(px + 1,     py - r),     -1);
    ret.emplace_back(Position(px + 1,     py + r),     -1);
    ret.emplace_back(Position(px + 1,     py + r + 1), -1);
    
    return ret;
}

void rectangle_propagate() {
    // Swipe once, left to right
    for (int y = 0; y <= y_max; ++y) {
        for (int x = 1; x <= x_max; ++x) {
            rectangle_board[y][x] += rectangle_board[y][x - 1];
        }
    }
    
    // Swipe once, top to bottom
    for (int x = 0; x <= x_max; ++x) {
        for (int y = 1; y <= y_max; ++y) {
            rectangle_board[y][x] += rectangle_board[y - 1][x];
        }
    }
}

void diamond_propagate() {
    // Swipe once, bottom left to top right (x + y = k)
    for (int k = 0; k <= x_max + y_max; ++k) {
        for (int x = max(k - y_max, 0) + 1; x <= min(k, x_max); ++x) {
            diamond_board[k - x][x] += diamond_board[k - (x - 1)][x - 1];
        }
    }
    
    // Swipe once, top left to bottom right (x - y = k)
    for (int k = -y_max; k <= x_max; ++k) {
        for (int x = max(k, 0) + 1; x <= min(k + y_max, x_max); ++x) {
            diamond_board[x - k][x] += diamond_board[(x - 1) - k][x - 1];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> x_max >> y_max >> num_shapes;
    
    rectangle_board.assign(y_max + 1, vector<int>(x_max + 1, 0));
    diamond_board.assign(y_max + 1, vector<int>(x_max + 1, 0));
    
    int type, px, py, qx, qy, r;
    for (int i = 0; i < num_shapes; ++i) {
        cin >> type;
        
        if (type == 1) {
            // Rectangle
            cin >> px >> py >> qx >> qy;
            for (auto [pos, value] : rectangle_markers(px, py, qx, qy)) {
                if (!in_range(pos.x, pos.y)) continue;
                rectangle_board[pos.y][pos.x] += value;
            }
        } else {
            // Diamond
            cin >> px >> py >> r;
            for (auto [pos, value] : diamond_markers(px, py, r)) {
                if (!in_range(pos.x, pos.y)) continue;
                diamond_board[pos.y][pos.x] += value;
            }
        }
    }
    
    rectangle_propagate();
    diamond_propagate();
    
    for (int y = 0; y < y_max; ++y) {
        for (int x = 0; x < x_max; ++x) {
            int cell = (rectangle_board[y][x] + diamond_board[y][x]) % 2;
            cout << (cell == 1 ? '#' : '.');
        }
        cout << '\n';
    }
    
    return 0;
}
