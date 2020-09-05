#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int T, a, b;
vector<int> prime;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    vector<bool> isPrime(10000, true);
    for (int i=2; i<=10000; ++i) {
        if (!isPrime[i]) continue;
        for (int j=i*i; j<10000; j+=i) {
            isPrime[j] = false;
        }
        if (1000 <= i && i < 10000) {
            prime.push_back(i);
        }
    }
    
    cin >> T;
    for (int t=0; t<T; ++t) {
        cin >> a >> b;
        
        int ans = -1;
        vector<bool> visited(10000, false);
        queue<pair<int, int>> q;
        q.push(make_pair(0, a));
        visited[a] = true;
        
        while (!q.empty()) {
            int dst = q.front().first;
            int cur = q.front().second;
            q.pop();
            
            if (cur == b) {
                ans = dst;
                break;
            }
            
            for (int radix=1; radix<10000; radix*=10) {
                for (int i=0; i<10; ++i) {
                    int next = cur - cur/radix*radix + cur/(radix*10)*(radix*10) + i*radix;
                    if (binary_search(prime.begin(), prime.end(), next) && !visited[next]) {
                        q.push(make_pair(dst+1, next));
                        visited[next] = true;
                    }
                }
            }
        }
        
        if (ans != -1) cout << ans << "\n";
        else cout << "Impossible\n";
    }
    
    return 0;
}
