#include <iostream>
#include <string.h>

using namespace std;

int n, W;
int cache[101][100001];
int Weight[101];
int Value[101];

int maxValue(int item, int maxWeight) {
    if (item == n) return 0;
    
    int& ret = cache[item][maxWeight];
    if (ret != -1) return ret;
    
    int curWeight = Weight[item];
    int curValue = Value[item];
    
    int include = 0;
    int declude = maxValue(item+1, maxWeight);
    
    if (curWeight <= maxWeight)
        include = curValue + maxValue(item+1, maxWeight - curWeight);
    
    return ret = max(include, declude);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> W;
    for (int i=0; i<n; i++) cin >> Weight[i] >> Value[i];
    
    memset(cache, -1, sizeof(cache));
    
    cout << maxValue(0, W);

    return 0;
}
