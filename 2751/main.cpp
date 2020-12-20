#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> arr;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    arr.assign(N, 0);
    for (int i=0; i<N; ++i) cin >> arr[i];
    sort(arr.begin(), arr.end());
    
    for (int i=0; i<N; ++i) cout << arr[i] << "\n";
    
    return 0;
}
