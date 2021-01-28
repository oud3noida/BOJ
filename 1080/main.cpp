#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int DELTA[3] = {-1, 0, 1};
int max_x, max_y, num_flip;
vector<string> initial_matrix;
vector<vector<bool>> matrix;

void flip_3x3(int x, int y) {
    for (int d=0; d<9; ++d) {
        int x_cur = x + DELTA[d%3],
            y_cur = y + DELTA[d/3];
        matrix[y_cur][x_cur] = !matrix[y_cur][x_cur];
    }
}

bool flip_matrix(int x, int y) {
    if (y == max_y - 1) {
        for (int _y=max_y-2; _y<max_y; ++_y) {
            for (int _x=0; _x<max_x; ++_x) {
                if (!matrix[_y][_x]) return false;
            }
        }
        return true;
    }

    if (x == max_x - 2) {
        if (matrix[y-1][x-1] == matrix[y-1][x] && matrix[y-1][x] == matrix[y-1][x+1]) {
            if (!matrix[y-1][x-1]) {
                flip_3x3(x, y);
                ++num_flip;
            }
            return flip_matrix(1, y + 1);
        } else return false;
    }

    if (!matrix[y-1][x-1]) {
        flip_3x3(x, y);
        ++num_flip;
    }
    return flip_matrix(x + 1, y);
}

bool is_matrix_convertible() {
    if (max_x < 3 || max_y < 3) {
        for (int _y=0; _y<max_y; ++_y) {
            for (int _x=0; _x<max_x; ++_x) {
                if (!matrix[_y][_x]) return false;
            }
        }
        return true;
    }

    return flip_matrix(1, 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> max_y >> max_x;

    initial_matrix.resize(max_y);
    for (int y=0; y<max_y; ++y) cin >> initial_matrix[y];

    matrix.assign(max_y, vector<bool>(max_x, true));
    string row;
    for (int y=0; y<max_y; ++y) {
        cin >> row;
        for (int x=0; x<max_x; ++x) {
            matrix[y][x] = (initial_matrix[y][x] == row[x]);
        }
    }

    num_flip = 0;
    if (is_matrix_convertible()) cout << num_flip;
    else cout << -1;

    return 0;
}