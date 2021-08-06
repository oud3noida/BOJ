#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int left_down, right_down;
    
    Edge(int left_down, int right_down)
        : left_down(left_down), right_down(right_down) {}
};

int x_max, y_max, max_diamond;
vector<string> board;
vector<vector<Edge>> edge;
vector<vector<bool>> visited;

bool in_range(int x, int y) {
    return 0 <= x && x < x_max && 0 <= y && y < y_max;
}

void find_edge(int x, int y) {
    int &left_down = edge[y][x].left_down,
        &right_down = edge[y][x].right_down;
    if (left_down != -1 && right_down != -1) return;
    
    if (board[y][x] == '0') {
        left_down = 0;
        right_down = 0;
        return;
    }
    
    left_down = 1;
    right_down = 1;
    
    if (in_range(x-1, y+1)) {
        find_edge(x-1, y+1);
        left_down += edge[y+1][x-1].left_down;
    }
    if (in_range(x+1, y+1)) {
        find_edge(x+1, y+1);
        right_down += edge[y+1][x+1].right_down;
    }
}

int possible_size(int x, int y) {
    return min(min(x + 1, x_max - x), (y_max - y + 1)/2);
}

void find_diamond(int x, int y) {
    if (!in_range(x, y) || visited[y][x]) return;
    visited[y][x] = true;
    
    if (possible_size(x, y) <= max_diamond) return;
    
    int &left_down = edge[y][x].left_down,
        &right_down = edge[y][x].right_down;
    int edge_length = min(left_down, right_down);
    
    if (edge_length > 0) {
        for (int l = edge_length; l > max_diamond; --l) {
            bool left_curve = edge[y + (l - 1)][x - (l - 1)].right_down >= l,
                 right_curve = edge[y + (l - 1)][x + (l - 1)].left_down >= l;
            
            if (left_curve && right_curve) {
                max_diamond = l;
                break;
            }
        }
    }
    
    find_diamond(x-1, y);
    find_diamond(x+1, y);
    find_diamond(x, y+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> y_max >> x_max;
    
    board.assign(y_max, string());
    for (int y=0; y<y_max; ++y) {
        cin >> board[y];
    }
    
    edge.assign(y_max, vector<Edge>(x_max, Edge(-1, -1)));
    for (int y = 0; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            find_edge(x, y);
        }
    }
    
    visited.assign(y_max, vector<bool>(x_max, false));
    max_diamond = 0;
    find_diamond(x_max/2, 0);
    
    cout << max_diamond;
    
    return 0;
}
