#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

typedef pair<int, int> intPair;

int n, w;
vector<intPair> cases;
vector<vector<int>> cache;
stack<int> policeCar;

int dst(int carNum, int case1, int case2) {
    int x1, y1,
        x2 = cases[case2].first,
        y2 = cases[case2].second;
    
    if (case1 != 0) {
        x1 = cases[case1].first;
        y1 = cases[case1].second;
    } else if (carNum == 1) {
        x1 = 1;
        y1 = 1;
    } else if (carNum == 2) {
        x1 = n;
        y1 = n;
    } else {
        assert(false);
        return -1;
    }
    
    return abs(x1 - x2) + abs(y1 - y2);
}

int minDst(int a, int b) {
    int &ret = cache[a][b];
    
    if (ret != -1) return ret;
    
    if (a == w) return ret = 0;
    if (b == w) return ret = 0;
    
    int nextCase = max(a, b) + 1;
    
    int move1 = minDst(nextCase, b) + dst(1, a, nextCase),
        move2 = minDst(a, nextCase) + dst(2, b, nextCase);
    
    return ret = min(move1, move2);
}

void traceCar(int a, int b) {
    if (a == w || b == w) return;
    
    int nextCase = max(a, b) + 1;
    
    int move1 = minDst(nextCase, b) + dst(1, a, nextCase),
        move2 = minDst(a, nextCase) + dst(2, b, nextCase);
    
    if (move1 < move2) {
        cout << "1\n";
        traceCar(nextCase, b);
    } else {
        cout << "2\n";
        traceCar(a, nextCase);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> w;
    
    cases.assign(w+1, make_pair(0, 0));
    for (int i=1; i<=w; ++i) cin >> cases[i].first >> cases[i].second;
    cache.assign(w+1, vector<int>(w+1, -1));
    
    cout << minDst(0, 0) << "\n";
    traceCar(0, 0);
    
    return 0;
}
