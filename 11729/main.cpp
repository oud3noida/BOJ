#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> moves;

void move_hanoi_tower(int disk, int from, int to) {
    if (disk == 1) {
        moves.emplace_back(from, to);
        return;
    }
    
    move_hanoi_tower(disk-1, from, to^from);
    moves.emplace_back(from, to);
    move_hanoi_tower(disk-1, to^from, to);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    move_hanoi_tower(n, 1, 3);
    
    cout << moves.size() << '\n';
    for (auto &move : moves) {
        cout << move.first << ' ' << move.second << '\n';
    }
    
    return 0;
}
