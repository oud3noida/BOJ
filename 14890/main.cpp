#include <iostream>
#include <vector>

using namespace std;

int n, length, ans;
vector<vector<int>> board;
vector<bool> occupied;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> length;
    
    board.assign(n, vector<int>(n, 0));
    for (int y=0; y<n; ++y)
        for (int x=0; x<n; ++x)
            cin >> board[y][x];
    ans = 0;
    
    for (int y=0; y<n; ++y) {
        occupied.assign(n, false);
        bool pass = true;
        
        int x = 1;
        while (pass && x < n) {
            int prev = board[y][x-1],
                cur  = board[y][x];
            
            if (abs(prev-cur) > 1) {
                pass = false;
            } else if (prev > cur) {
                for (int i=0; i<length; ++i) {
                    if (x+i >= n || board[y][x+i] != cur) {
                        pass = false;
                        break;
                    }
                    occupied[x+i] = true;
                }
                x += length;
            } else if (prev < cur) {
                for (int i=1; i<=length; ++i) {
                    if (x-i < 0 || board[y][x-i] != prev || occupied[x-i]) {
                        pass = false;
                        break;
                    }
                    occupied[x-i] = true;
                }
                ++x;
            } else ++x;
        }
        
        if (pass) ++ans;
    }
    
    for (int x=0; x<n; ++x) {
        occupied.assign(n, false);
        bool pass = true;
        
        int y = 1;
        while (pass && y < n) {
            int prev = board[y-1][x],
                cur  = board[y][x];
            
            if (abs(prev-cur) > 1) {
                pass = false;
            } else if (prev > cur) {
                for (int i=0; i<length; ++i) {
                    if (y+i >= n || board[y+i][x] != cur) {
                        pass = false;
                        break;
                    }
                    occupied[y+i] = true;
                }
                y += length;
            } else if (prev < cur) {
                for (int i=1; i<=length; ++i) {
                    if (y-i < 0 || board[y-i][x] != prev || occupied[y-i]) {
                        pass = false;
                        break;
                    }
                    occupied[y-i] = true;
                }
                ++y;
            } else ++y;
        }
        
        if (pass) ++ans;
    }
    
    cout << ans;
    
    return 0;
}
