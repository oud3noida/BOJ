#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> price(n, 0);
    for (int i=0; i<n; ++i) cin >> price[i];

    for (int i=0; i<n; ++i) {
        for (int j=1; j<=(i+1)/2; ++j) {
            price[i] = min(price[i], price[i-j] + price[j-1]);
        }
    }

    cout << price[n-1];

    return 0;
}