#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, period, maxTime, ans;
vector<pair<int, int>> tests;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> period >> maxTime;
    
    int a, b;
    for (int i=0; i<N; ++i) {
        cin >> a >> b;
        tests.push_back(make_pair(a, a+b));
    }
    
    tests.push_back(make_pair(0, 0));
    tests.push_back(make_pair(maxTime, maxTime));
    
    sort(tests.begin(), tests.end());
    
    ans = -1;
    for (int i=0; i<N+1; ++i) {
        if (tests[i].second + period <= tests[i+1].first) {
            ans = tests[i].second;
            break;
        }
    }
    cout << ans;
    
    return 0;
}