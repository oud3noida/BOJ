#include <iostream>
#include <vector>

using namespace std;

int n, min_num_tail;
vector<vector<bool>> is_head;

void flip_column(int column, int sum_num_tail) {
    if (column == n) {
        min_num_tail = min(min_num_tail, sum_num_tail);
        return;
    }

    int num_tail = 0;
    for (int row=0; row<n; ++row) {
        if (!is_head[row][column]) ++num_tail;
    }

    if (num_tail <= n/2)
        flip_column(column + 1, sum_num_tail + num_tail);
    else
        flip_column(column + 1, sum_num_tail + n - num_tail);
}

void flip_one_row(int row) {
    for (int column=0; column<n; ++column) {
        is_head[row][column] = !is_head[row][column];
    }
}

void flip_row(int row) {
    if (row == n) return flip_column(0, 0);
    flip_one_row(row);
    flip_row(row + 1);
    flip_one_row(row);
    flip_row(row + 1);
}

void flip_coins() {
    flip_row(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    is_head.assign(n, vector<bool>(n, true));
    char coin;
    for (int y=0; y<n; ++y) {
        for (int x=0; x<n; ++x) {
            cin >> coin;
            is_head[y][x] = (coin == 'H');
        }
    }

    min_num_tail = n*n;
    flip_coins();
    cout << min_num_tail;

    return 0;
}