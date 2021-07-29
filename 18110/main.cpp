#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr double EXCLUDE = 0.15;
int n;
vector<int> opinions;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    opinions.assign(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> opinions[i];
    }
    sort(opinions.begin(), opinions.end());
    
    int exclude = round(n * EXCLUDE);
    
    double sum = 0;
    for (int i=exclude; i<n-exclude; ++i) {
        sum += opinions[i];
    }
    
    if (n > 0) cout << round(sum / (n-2*exclude));
    else cout << 0;
    
    return 0;
}
