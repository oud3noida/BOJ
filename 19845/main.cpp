#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, Q, x, y, xAns, yAns;
vector<int> row;

bool comp(int a, int b) {
    return a > b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> Q;
    
    row.assign(N, 0);
    for (int i=0; i<N; ++i) cin >> row[i];
    
    for (int i=0; i<Q; ++i) {
        cin >> x >> y;
        
        xAns = upper_bound(row.begin(), row.end(), x, comp) - row.begin() - (y-1);
        if (xAns < 0) xAns = 0;
        yAns = row[y-1] - x;
        if (yAns < 0) yAns = 0;
        
        cout << xAns + yAns << "\n";
    }
    
    return 0;
}