#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 100000, DIR = 4, INF = 987654321;
int n, foot1, foot2;
int command[MAX], cache[MAX][DIR+1][DIR+1];

int cost(int before, int after) {
    // 0: End of the game
    if (!after) return 0;
    // 1: Step on the same button once again
    if (before == after) return 1;
    // 2: Move from the center to one of the buttons
    if (!before) return 2;
    // 4: Move from one opposite to another
    if (abs(before-after) == 2) return 4;
    // 3: Move onto the adjacent button
    return 3;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int minCost(int cur, int foot1, int foot2) {
    if (cur == n) return 0;
    
    if (foot1 > foot2) swap(foot1, foot2);
    
    int nextFoot = command[cur];
    int &ret = cache[cur][foot1][foot2];
    if (ret != -1) return ret;
    
    ret = min(minCost(cur+1, nextFoot, foot2) + cost(foot1, nextFoot),
              minCost(cur+1, foot1, nextFoot) + cost(foot2, nextFoot));
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    memset(cache, -1, sizeof(cache));
    
    n = 0;
    int tmp;
    do {
        cin >> tmp;
        command[n++] = tmp;
    } while (tmp != 0);
    --n;
    
    cout << minCost(0, 0, 0);
    
    return 0;
}
