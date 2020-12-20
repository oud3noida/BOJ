#include <iostream>
#include <vector>

using namespace std;

int N, denom, x, top;
double ans;
vector<int> p;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> denom;
    p.assign(denom, 1);
    top = denom;
    
    for (int q=1; q<N; ++q) {
        cin >> x;
        if (x >= top) continue;
        
        for (int i=x; i<top; ++i) {
            p[i%x] += p[i];
        }
        top = x;
    }
    
    ans = 0;
    for (int i=0; i<top; ++i) {
        ans += i * p[i];
    }
    
    cout.precision(12);
    cout << ans / denom;
    
    return 0;
}