#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    int n;
    cin >> n;

    vector<int> arr(n, -1), nge_index(n, -1);
    for (int i=0; i<n; ++i) cin >> arr[i];

    for (int i=n-2; i>=0; --i) {
        int x = i+1;
        while (x != -1 && arr[i] >= arr[x]) x = nge_index[x];
        nge_index[i] = x;
    }

    for (int i=0; i<n; ++i) {
        if (nge_index[i] == -1) cout << -1 << " ";
        else cout << arr[nge_index[i]] << " ";
    }

    return 0;
}