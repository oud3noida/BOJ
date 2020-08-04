#include <iostream>
#include <vector>

using namespace std;

const int DX[4] = {1, 0, -1, 0},
          DY[4] = {0, -1, 0, 1};
int N, ans;
vector<vector<bool>> grid;

void makeDragonCurve(int x, int y, int dir, int gen) {
    vector<int> directions(1<<10, -1);
    directions[0] = dir;
    int cnt = 1;
    
    for (; gen>0; --gen) {
        for (int i=0; i<cnt; ++i)
            directions[2*cnt - i - 1] = (directions[i] + 1) % 4;
        cnt = cnt << 1;
    }
    
    grid[y][x] = true;
    for (int i=0; i<cnt; ++i) {
        x += DX[directions[i]];
        y += DY[directions[i]];
        grid[y][x] = true;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    grid.assign(101, vector<bool>(101, false));
    
    cin >> N;
    
    int x, y, d, g;
    for (int i=0; i<N; ++i) {
        cin >> x >> y >> d >> g;
        makeDragonCurve(x, y, d, g);
    }
    
    ans = 0;
    for (int y=1; y<=100; ++y) {
        for (int x=1; x<=100; ++x) {
            if (grid[y-1][x-1] && grid[y-1][x] && grid[y][x-1] && grid[y][x])
                ++ans;
        }
    }
    
    cout << ans;
    
    return 0;
}
