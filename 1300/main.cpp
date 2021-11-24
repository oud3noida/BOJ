#include <iostream>
#include <vector>

using namespace std;

long long n, k;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    long long left = 1, right = n * n;
    
    while (left < right) {
        long long mid = (left + right) / 2;
        
        long long result = 0;
        for (long long i = 1; i <= n; i++) {
            result += min(n, mid / i);
        }
        
        if (result >= k) right = mid;
        else left = mid + 1;
    }
    
    cout << left;
    
    return 0;
}
