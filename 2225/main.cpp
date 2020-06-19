#include <iostream>

using namespace std;

const int MOD = 1000000000;
int n, k;
int arr[201][201];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> k;
    
    for (int v=0; v<n+1; v++) {
        for (int i=0; i<k+1; i++) {
            if (v == 0 || i == 1) arr[v][i] = 1;
            else arr[v][i] = 0;
        }
    }
    
    for (int v=1; v<n+1; v++) {
        for (int i=2; i<k+1; i++) {
            arr[v][i] = (arr[v-1][i] + arr[v][i-1]) % MOD;
        }
    }
    
    cout << arr[n][k];

    return 0;
}
