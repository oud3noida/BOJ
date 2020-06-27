#include <iostream>

using namespace std;

const int INF = 999;
// (Center, Up, Down, Left, Right)
const int DX[5] = {0, 0, 0, -1, 1},
          DY[5] = {0, -1, 1, 0, 0};
bool bulbs[10][10];

bool inRange(int x, int y) {
    return (0 <= x) && (x < 10) && (0 <= y) && (y < 10);
}

void pressSwitch(int a, int b) {
    for (int dir=0; dir<5; ++dir) {
        int x = a + DX[dir],
            y = b + DY[dir];
        
        if (!inRange(x, y)) continue;
        bulbs[y][x] = !bulbs[y][x];
    }
}

int minSwitch(int x, int y) {
    if (x == 10) return minSwitch(0, y+1);
    if (y == 10) {
        bool clear = true;
        
        for (int i=0; i<10; ++i) {
            clear = clear && !bulbs[9][i];
        }
        
        if (clear) return 0;
        else return INF;
    }
    
    int ret = INF;
    
    // Skip this switch
    if (y == 0 || !bulbs[y-1][x]) ret = min(ret, minSwitch(x+1, y));
    
    // Press this switch
    pressSwitch(x, y);
    if (y == 0 || !bulbs[y-1][x]) ret = min(ret, 1 + minSwitch(x+1, y));
    pressSwitch(x, y);
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    string tmp;
    for (int y=0; y<10; y++) {
        cin >> tmp;
        for (int x=0; x<10; x++) {
            bulbs[y][x] = (tmp[x] == 'O');
        }
    }
    
    int ans = minSwitch(0, 0);
    
    cout << ((ans < INF) ? ans : -1);
    
    return 0;
}
