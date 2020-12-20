#include <iostream>
#include <vector>

using namespace std;

int N;
int numIncrease, numDecrease, kIncrease, kDecrease;
vector<int> arr;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    numIncrease = 0;
    numDecrease = 0;
    kIncrease = 0;
    kDecrease = 0;
    
    int ith;
    for (int i=0; i<=N; ++i) {
        if (i != N) {
            cin >> ith;
            arr.push_back(ith);
        }
        if (i == 0) continue;
        
        if (arr[i-1] < arr[i%N]) {
            if (++numIncrease == 1) kIncrease = i;
        } else if (arr[i-1] > arr[i%N]) {
            if (++numDecrease == 1) kDecrease = i;
        }
    }
    
    if (kIncrease % N == 0 || kDecrease % N == 0) cout << 0;
    else if (numIncrease == 1 && numDecrease == 1) cout << min(kIncrease, kDecrease);
    else if (numIncrease == 1) cout << kIncrease;
    else if (numDecrease == 1) cout << kDecrease;
    else cout << -1;
    
    return 0;
}