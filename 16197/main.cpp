#include <iostream>
#include <vector>

using namespace std;

const int INF = 11;
const char COIN = 'o',
           BLANK = '.',
           WALL = '#';
enum Direction {UP, DOWN, LEFT, RIGHT, INIT};
int x_max, y_max;
int min_num_press;
vector<vector<char>> board;
vector<vector<bool>> visited;

struct Position {
    int x, y;
    Position(int x=-1, int y=-1) : x(x), y(y) {}
};

pair<Position, Position> coins;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

bool is_coin_fallen_when_moved(Position &coin, Direction direction) {
    int dx[4] = {0, 0, -1, 1},
        dy[4] = {-1, 1, 0, 0};
    
    int dir = (int) direction;
    int x_new = coin.x + dx[dir],
        y_new = coin.y + dy[dir];
        
    if (in_range(x_new, y_new) && board[y_new][x_new] == WALL)
        return false;
    
    coin = Position(x_new, y_new);
    return !in_range(x_new, y_new);
}

int num_fallen_coins_when_moved(Direction direction) {
    int num_fallen_coins = 0;
    
    if (is_coin_fallen_when_moved(coins.first, direction))
        ++num_fallen_coins;
    if (is_coin_fallen_when_moved(coins.second, direction))
        ++num_fallen_coins;
    
    return num_fallen_coins;
}

void press_button(int cur, Direction prev_dir) {
    if (cur >= min_num_press) return;
    
    pair<Position, Position> tmp_coins;
    Direction directions[4] = {UP, DOWN, LEFT, RIGHT};
    
    for (const auto dir : directions) {
        int x1 = coins.first.x,
            x2 = coins.second.x,
            y1 = coins.first.y,
            y2 = coins.second.y;
        if (visited[x1*y_max+y1][x2*y_max+y2]) continue;
        
        cout << dir << endl;
        
        visited[x1*y_max+y1][x2*y_max+y2] = true;
        
        tmp_coins = coins;
        
        int num_fallen_coins = num_fallen_coins_when_moved(dir);
        
        if (num_fallen_coins == 1) {
            min_num_press = min(min_num_press, cur);
            
            coins = tmp_coins;
            visited[x1*y_max+y1][x2*y_max+y2] = false;
            
            return;
        } else if (num_fallen_coins == 0) {
            press_button(cur + 1, dir);
        }
        
        visited[x1*y_max+y1][x2*y_max+y2] = false;
        coins = tmp_coins;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> y_max >> x_max;
    board.assign(y_max, vector<char>(x_max, '.'));
    
    char cell;
    bool found_coin = false;
    for (int y=0; y<y_max; ++y) {
        for (int x=0; x<x_max; ++x) {
            cin >> cell;
            board[y][x] = cell;
            
            if (cell == COIN) {
                if (!found_coin) {
                    found_coin = true;
                    coins.first = Position(x, y);
                } else {
                    coins.second = Position(x, y);
                }
                board[y][x] = BLANK;
            }
        }
    }
    
    min_num_press = INF;
    visited.assign(x_max*y_max, vector<bool>(x_max*y_max, false));
    
    press_button(1, INIT);
    
    if (min_num_press == INF)
        cout << -1;
    else
        cout << min_num_press;

    return 0;
}
