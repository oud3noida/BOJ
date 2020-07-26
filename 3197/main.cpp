#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> intPair;

const int DX[4] = {-1, 1, 0, 0},
          DY[4] = {0, 0, -1, 1};
int X, Y, ans;
intPair swan1, swan2;
vector<vector<char>> lake;
vector<vector<intPair>> parent;
queue<intPair> iceQ;

bool inRange(int x, int y) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

intPair find(intPair a) {
    if (a != parent[a.second][a.first])
        return parent[a.second][a.first] = find(parent[a.second][a.first]);
    return a;
}

void merge(intPair a, intPair b) {
    parent[find(a).second][find(a).first] = find(b);
}

void meltIce() {
    queue<intPair> tmpQ;
    vector<vector<bool>> visited(Y, vector<bool>(X, false));
    
    // Update ice cells in the queue into water cells
    //   (Hereinafter we call these cells 'molten ice cells')
    while (!iceQ.empty()) {
        intPair cur = iceQ.front(); iceQ.pop();
        int x = cur.first,
            y = cur.second;
        
        lake[y][x] = '.';
        tmpQ.push(cur);
    }
    
    iceQ = tmpQ;
    tmpQ = queue<intPair>();
    
    // Update the queue and the union-find structure
    while (!iceQ.empty()) {
        intPair cur = iceQ.front(); iceQ.pop();
        int x = cur.first,
            y = cur.second;
        
        for (int i=0; i<4; ++i) {
            int xNext = x+DX[i], yNext = y+DY[i];
            if (!inRange(xNext, yNext)) continue;
            
            // If an ice cell is adjacent to the molten ice cell,
            //   store it into the queue
            if (lake[yNext][xNext] == 'X') {
                if (visited[yNext][xNext]) continue;
                tmpQ.push(make_pair(xNext, yNext));
                visited[yNext][xNext] = true;
            }
            // Merge water cells that are adjacent to each other,
            //   including the molten ice cells
            else merge(cur, make_pair(xNext, yNext));
        }
    }
    
    iceQ = tmpQ;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    swan1 = make_pair(-1, -1);
    
    cin >> Y >> X;
    
    // Initialize the lake array
    lake.assign(Y, vector<char>(X, '.'));
    parent.assign(Y, vector<intPair>(X, make_pair(-1, -1)));
    for (int y=0; y<Y; ++y) {
        for (int x=0; x<X; ++x) {
            // Initialize the union-find structure
            parent[y][x] = make_pair(x, y);
            
            cin >> lake[y][x];
            
            if (lake[y][x] == 'X') continue;
            
            // Merge water cells that are adjacent to each other
            if (inRange(x-1, y) && lake[y][x-1] != 'X')
                merge(make_pair(x-1, y), make_pair(x, y));
            if (inRange(x, y-1) && lake[y-1][x] != 'X')
                merge(make_pair(x, y-1), make_pair(x, y));
            
            // Store the position of each swan
            if (lake[y][x] == 'L' && swan1.first == -1) {
                swan1 = make_pair(x, y);
                lake[y][x] = '.';
            } else if (lake[y][x] == 'L') {
                swan2 = make_pair(x, y);
                lake[y][x] = '.';
            }
        }
    }
    
    // Store ice cells into the queue that will melt within a day
    for (int y=0; y<Y; ++y) {
        for (int x=0; x<X; ++x) {
            if (lake[y][x] != 'X') continue;
            for (int i=0; i<4; ++i) {
                int xNext = x+DX[i], yNext = y+DY[i];
                if (!inRange(xNext, yNext)) continue;
                if (lake[yNext][xNext] == 'X') continue;
                iceQ.push(make_pair(x, y));
                break;
            }
        }
    }
    
    // Proceed until two swans are in the same water cell set
    ans = 0;
    while (find(swan1) != find(swan2)) {
        meltIce();
        ++ans;
    }
    
    cout << ans;
    
    return 0;
}
