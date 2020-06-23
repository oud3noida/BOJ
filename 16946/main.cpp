#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX = 1000;
const int XDIR[4] = {-1, 1, 0, 0},
          YDIR[4] = {0, 0, -1, 1};
int X, Y;

struct Pos {
    int x, y;
    Pos(int a=-1, int b=-1) : x(a), y(b) {}
    
    bool operator<(Pos const& other) const {
        if (x != other.x) return (x < other.x);
        return (y < other.y);
    }
    
    bool operator==(Pos const& other) const {
        return (x == other.x) && (y == other.y);
    }
    
    bool operator!=(Pos const& other) const {
        return (x != other.x) || (y != other.y);
    }
};

class Map {
    private:
    vector<vector<bool>> wall;
    vector<vector<Pos>> parent;
    vector<vector<int>> size;
    
    public:
    Map(int X, int Y) {
        wall.assign(MAX, vector<bool>(MAX, false));
        parent.assign(MAX, vector<Pos>(MAX, Pos()));
        size.assign(MAX, vector<int>(MAX, 1));
        
        for (int y=0; y<Y; y++) {
            for (int x=0; x<X; x++) {
                parent[y][x] = Pos(x, y);
            }
        }
    }
    
    // ------ Property getter/setter functions ------
    
    bool isWall(int x, int y) {
        return wall[y][x];
    }
    
    void setWall(int x, int y, bool b) {
        wall[y][x] = b;
        if (b) size[y][x] = 0;
    }
    
    // EXACTLY SAME AS FIND() FUNCTION; UNNECESSARY
    /*
    Pos getID(int x, int y) {
        return find(x, y);
    }
    */
    
    int getSize(int x, int y) {
        Pos p = find(x, y);
        return size[p.y][p.x];
    }
    
    // ----- Functions for Union-Find structure -----
    
    void merge(int x1, int y1, int x2, int y2) {
        if (find(x1, y1) == find(x2, y2)) return;
        
        Pos p1 = find(x1, y1),
            p2 = find(x2, y2);
        
        parent[p1.y][p1.x] = Pos(p2.x, p2.y);
        size[p2.y][p2.x] += size[p1.y][p1.x];
    }
    
    Pos find(int x, int y) {
        if (Pos(x, y) != parent[y][x])
            parent[y][x] = find(parent[y][x]);
        return parent[y][x];
    }
    
    Pos find(Pos p) {
        return find(p.x, p.y);
    }
};

bool inRange(int x, int y) {
    return (0 <= x) && (x < X) && (0 <= y) && (y < Y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X;
    Map myMap(X, Y);
    
    string cells;
    for (int y=0; y<Y; y++) {
        cin >> cells;
        for (int x=0; x<X; x++) {
            myMap.setWall(x, y, cells[x] == '1');
        }
    }
    
    // Merge adjacent blank cells together
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            if (myMap.isWall(x, y)) continue;
            
            if (inRange(x+1, y) && !myMap.isWall(x+1, y))
                myMap.merge(x, y, x+1, y);
            if (inRange(x, y+1) && !myMap.isWall(x, y+1))
                myMap.merge(x, y, x, y+1);
        }
    }
    
    set<Pos> ID;
    int ans;
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            if (!myMap.isWall(x, y)) {
                cout << 0;
                continue;
            }
            
            ans = 1;
            ID.clear();
            
            for (int d=0; d<4; d++) {
                if (!inRange(x+XDIR[d], y+YDIR[d])) continue;
                
                Pos adj = myMap.find(x+XDIR[d], y+YDIR[d]);
                
                // Every cell chunk must be visited at most once
                if (ID.find(adj) != ID.end()) continue;
                
                ans += myMap.getSize(x+XDIR[d], y+YDIR[d]);
                ID.insert(adj);
            }
            
            cout << ans%10;
        }
        cout << "\n";
    }
    
    return 0;
}
