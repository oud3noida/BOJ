#include <iostream>
#include <vector>

using namespace std;

const int MAX = 10, DMAX = 19;
int n;
bool board[MAX][MAX], diagonal[DMAX];

int bishop(int row) {
    if (row > 2*(n-1)) return 0;
    
    // Skip this cell
    int ret = bishop(row+2);
    
    for (int i=max(0, row-(n-1)); i<=min(row, n-1); i++) {
        if (!board[row-i][i] || diagonal[n-1 + row - 2*i])  // Unable to place bishop
            continue;
        
        // Place bishop on this cell
        diagonal[n-1 + row - 2*i] = true;
        ret = max(ret, 1+bishop(row+2));
        diagonal[n-1 + row - 2*i] = false;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    for (int y=0; y<n; y++) {
        for (int x=0; x<n; x++) {
            cin >> board[y][x];
        }
    }
    
    cout << bishop(0) + bishop(1);
    
    return 0;
}
