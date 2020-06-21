#include <iostream>
#include <vector>

using namespace std;

int X, Y, T;
vector<vector<int>> house;
vector<vector<int>> nextHouse;
int cleanerTop, cleanerBottom;

void moveDust() {
    nextHouse.assign(Y, vector<int>(X, 0));
    
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            int dir = 0;
            if (house[y][x] <= 0) {
                if (house[y][x] == -1) nextHouse[y][x] = house[y][x];
                continue;
            }
            
            if (x > 0 && house[y][x-1] != -1) {         // Left
                nextHouse[y][x-1] += house[y][x] / 5;
                dir++;
            } if (y > 0 && house[y-1][x] != -1) {       // Up
                nextHouse[y-1][x] += house[y][x] / 5;
                dir++;
            } if (x < X-1 && house[y][x+1] != -1) {     // Right
                nextHouse[y][x+1] += house[y][x] / 5;
                dir++;
            } if (y < Y-1 && house[y+1][x] != -1) {     // Down
                nextHouse[y+1][x] += house[y][x] / 5;
                dir++;
            }
            
            nextHouse[y][x] += (house[y][x] - (house[y][x] / 5) * dir);
        }
    }
    
    // Update the house map
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            house[y][x] = nextHouse[y][x];
        }
    }
}

pair<int, int> nextTop(int x, int y) {
    /*
        Returns the next cell.
        The area covers the cells above the air purifier.
        NOTE: We travel clockwise, 
              whereas the air circulates counter-clockwise in this area.
        (Beacuse a cell A is overwritten with the value from the cell nextTop(A),
         The air circulation proceeds in the opposite direction.)
    */
    if (y == cleanerTop) return make_pair(x-1, y);      // Downmost:  go left
    else if (x == X-1) return make_pair(x, y+1);        // Rightmost: go down
    else if (y == 0) return make_pair(x+1, y);          // Upmost:    go right
    else if (x == 0) return make_pair(x, y-1);          // Leftmost:  go up
    
    // ERROR
    return make_pair(-1, -1);
}

pair<int, int> nextBottom(int x, int y) {
    /*
        Refer to the comments from nextTop().
    */
    if (y == cleanerBottom) return make_pair(x-1, y);   // Upmost:    go left
    else if (x == X-1) return make_pair(x, y-1);        // Rightmost: go up
    else if (y == Y-1) return make_pair(x+1, y);        // Downmost:  go right
    else if (x == 0) return make_pair(x, y+1);          // Leftmost:  go down
    
    // ERROR
    return make_pair(-1, -1);
}

void moveAir() {
    pair<int, int> prev, cur;
    prev = make_pair(0, cleanerTop-1);
    cur = nextTop(prev.first, prev.second);
    while (!(cur.first == 0 && cur.second == cleanerTop)) {
        house[prev.second][prev.first] = house[cur.second][cur.first];
        prev = make_pair(cur.first, cur.second);
        cur = nextTop(prev.first, prev.second);
    }
    // Air purifier releases purified air (DUH)
    house[prev.second][prev.first] = 0;
    
    prev = make_pair(0, cleanerBottom+1);
    cur = nextBottom(prev.first, prev.second);
    while (!(cur.first == 0 && cur.second == cleanerBottom)) {
        house[prev.second][prev.first] = house[cur.second][cur.first];
        prev = make_pair(cur.first, cur.second);
        cur = nextBottom(prev.first, prev.second);
    }
    // Air purifier releases purified air
    house[prev.second][prev.first] = 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> Y >> X >> T;
    
    int dust;
    bool cleanerFound = false;
    house.assign(Y, vector<int>());
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            cin >> dust;
            // Cleaner
            if (dust == -1) {
                if (!cleanerFound) {
                    cleanerTop = y;
                    cleanerFound = true;
                } else cleanerBottom = y;
            }
            house[y].push_back(dust);
        }
    }
    
    for (int t=0; t<T; t++) {
        moveDust();
        moveAir();
    }
    
    int allDust = 0;
    for (int y=0; y<Y; y++) {
        for (int x=0; x<X; x++) {
            if (house[y][x] > 0) allDust += house[y][x];
        }
    }
    
    cout << allDust;
    
    return 0;
}
