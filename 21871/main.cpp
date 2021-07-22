#include <iostream>

using namespace std;

long long n, k;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    long long contaminated = (n-(k-1)/2)*(n-k/2+1)*2;
    if (k>2*n+1) cout << (2*n+1)*(2*n+1);
    else if (k%2==0) cout << (2*n+1)*(2*n+1) - contaminated - (k-1);
    else cout << (2*n+1)*(2*n+1) - contaminated;
    
    return 0;
}
