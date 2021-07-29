#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (a%b == 0) return b;
    return gcd(b, a%b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int num_tests;
    cin >> num_tests;
    
    for (int t=0; t<num_tests; ++t) {
        int n;
        cin >> n;
        
        vector<int> numbers(n, 0);
        for (int i=0; i<n; ++i) {
            cin >> numbers[i];
        }
        
        long long sum_gcd = 0;
        for (int a=0; a<n-1; ++a) {
            for (int b=a+1; b<n; ++b) {
                sum_gcd += gcd(numbers[a], numbers[b]);
            }
        }
        
        cout << sum_gcd << '\n';
    }
    
    return 0;
}
