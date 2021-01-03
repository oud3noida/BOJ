#include <iostream>
#include <vector>

using namespace std;

int X, Y;
vector<string> board;
vector<vector<bool>> dir_is_vertical;

int sum_partition() {
    int ret = 0;

    for (int y=0; y<Y; ++y) {
        int cur_sum = 0;
        for (int x=0; x<X; ++x) {
            if (!dir_is_vertical[y][x]) {
                cur_sum *= 10;
                cur_sum += (int) (board[y][x] - '0');
            } else {
                ret += cur_sum;
                cur_sum = 0;
            }
        }
        ret += cur_sum;
    }

    for (int x=0; x<X; ++x) {
        int cur_sum = 0;
        for (int y=0; y<Y; ++y) {
            if (dir_is_vertical[y][x]) {
                cur_sum *= 10;
                cur_sum += (int) (board[y][x] - '0');
            } else {
                ret += cur_sum;
                cur_sum = 0;
            }
        }
        ret += cur_sum;
    }

    return ret;
}

int max_sum_partition(int x, int y) {
    if (y == Y) return sum_partition();
    if (x == X) return max_sum_partition(0, y+1);

    dir_is_vertical[y][x] = true;
    int ret = max_sum_partition(x+1, y);
    dir_is_vertical[y][x] = false;
    return max(ret, max_sum_partition(x+1, y));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> Y >> X;
    board.assign(Y, "");
    for (int y=0; y<Y; ++y) cin >> board[y];

    dir_is_vertical.assign(Y, vector<bool>(X, false));
    cout << max_sum_partition(0, 0);

    return 0;
}