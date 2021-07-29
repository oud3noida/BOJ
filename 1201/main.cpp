#include <iostream>
#include <vector>

using namespace std;

int n, increasing, decreasing;

void print_range(int begin, int end) {
    for (int i=begin; i<=end; ++i)
        cout << i << ' ';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> increasing >> decreasing;
    
    if (increasing+decreasing-1 > n || increasing*decreasing < n) {
        cout << -1;
        return 0;
    }
    
    while (decreasing > 1 && decreasing-1 <= n-increasing) {
        print_range(n-increasing+1, n);
        n -= increasing;
        --decreasing;
    }
    while (decreasing > 1) {
        cout << n-- << ' ';
        --decreasing;
    }
    print_range(1, n);
    
    return 0;
}
