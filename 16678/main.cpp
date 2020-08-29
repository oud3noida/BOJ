#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
long long ans;
vector<int> honor;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    honor.assign(N, 0);
    
    for (int i=0; i<N; ++i) cin >> honor[i];
    sort(honor.begin(), honor.end());
    
    ans = 0;
    if (honor[0] > 1) {
        ans += honor[0] - 1;
        honor[0] = 1;
    }
    for (int i=1; i<N; ++i) {
        if (honor[i] - honor[i-1] > 1) {
            ans += honor[i] - honor[i-1] - 1;
            honor[i] = honor[i-1] + 1;
        }
    }
    
    cout << ans;
    
    return 0;
}
