#include <iostream>
#include <vector>
#include <set>
#include <string.h>

using namespace std;

struct fish {
    int size;
    pair<int, int> pos, speed;
    
    fish(pair<int, int> p, pair<int, int> s, int z) :
    size(z), pos(p), speed(s) {}
};

const int INF = 999;
int n, X, Y, ans;
fish* shark[10000];
set<pair<int, int>> aquarium[100][100]; // (size, fish)
set<int> depth[100];

void move(fish* shark) {
    int &x  = shark->pos.first,   &y  = shark->pos.second,
        &dx = shark->speed.first, &dy = shark->speed.second;
    
    bool reverse = false;
    x += dx;
    while (x < 0 || x >= X) {
        if (x < 0) x = 0 - x;
        else x = 2*(X-1) - x;
        reverse = !reverse;
    }
    if (reverse) dx = -1*dx;
    
    reverse = false;
    y += dy;
    while (y < 0 || y >= Y) {
        if (y < 0) y = 0 - y;
        else y = 2*(Y-1) - y;
        reverse = !reverse;
    }
    if (reverse) dy = -1*dy;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X >> n;
    
    int x, y, speed, dir, size;
    pair<int, int> p, s;
    for (int i=0; i<n; i++) {
        cin >> y >> x >> speed >> dir >> size;
        
        p = make_pair(x-1, y-1);
        
        switch (dir) {
            case 1: s = make_pair(0, -1*speed); break;
            case 2: s = make_pair(0, speed);    break;
            case 3: s = make_pair(speed, 0);    break;
            case 4: s = make_pair(-1*speed, 0); break;
        }
        
        shark[i] = new fish(p, s, size);
        aquarium[y-1][x-1].insert(make_pair(size, i));
        depth[x-1].insert(y-1);
    }
    
    ans = 0;
    // Start fishing for each column
    for (int cur=0; cur<X; cur++) {
        // Catch a shark with the least depth in this column
        // If there are no shark in this column, do nothing
        if (!depth[cur].empty()) {
            y = *(depth[cur].begin());
            int caughtShark = aquarium[y][cur].begin()->second;
            
            ans += shark[caughtShark]->size;
            
            depth[cur].erase(depth[cur].begin());
            aquarium[y][cur].clear();
            shark[caughtShark] = NULL;
        }
        
        // Move every shark, except for the caught ones
        // Allows more than one shark in a cell
        for (int i=0; i<n; i++) {
            if (shark[i] == NULL) continue;
            
            x    = shark[i]->pos.first;
            y    = shark[i]->pos.second;
            size = shark[i]->size;
            
            aquarium[y][x].erase(aquarium[y][x].find(make_pair(size, i)));
            if (aquarium[y][x].empty())
                depth[x].erase(depth[x].find(y));
            
            move(shark[i]);
            
            x = shark[i]->pos.first;
            y = shark[i]->pos.second;
            
            aquarium[y][x].insert(make_pair(size, i));
            depth[x].insert(y);
        }
        
        // If there are multiple sharks in one cell, leave the biggest one only
        for (int y=0; y<Y; y++) {
            for (int x=0; x<X; x++) {
                if (aquarium[y][x].size() > 1) {
                    auto biggestShark = --aquarium[y][x].end();
                    for (auto it = aquarium[y][x].begin(); it != biggestShark; ++it) {
                        shark[it->second] = NULL;
                    }
                    pair<int, int> tmp = *biggestShark;
                    aquarium[y][x].clear();
                    aquarium[y][x].insert(tmp);
                }
            }
        }
    }
    
    cout << ans;
}
