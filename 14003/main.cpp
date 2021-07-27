#include <iostream>
#include <vector>

using namespace std;

const int INF = 1987654321;
int n;
vector<int> arr, parent;
vector<pair<int, int>> minLast; // (val, idx)
int top;

int lisIdx(int j) {
    int left = 0, right = top;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[j] <= minLast[mid].first) right = mid;
        else left = mid + 1;
    }
    if (arr[j] > minLast[left].first) {
        minLast[++top] = make_pair(arr[j], j);
        return minLast[left].second;
    } else {
        minLast[left] = make_pair(arr[j], j);
        return minLast[left-1].second;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    arr.assign(1000001, 0);
    parent.assign(1000001, 0);
    minLast.assign(1000001, make_pair(0, 0));
    
    top = 0;
    minLast[0] = make_pair(-1*INF, -1);
    
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        parent[i] = lisIdx(i);
    }
    
    int cur = minLast[top].second;
    int lis[top];
    int j = -1;
    while (cur >= 0) {
        lis[++j] = arr[cur];
        cur = parent[cur];
    }
    
    cout << top << endl;
    for (int i=top-1; i>=0; i--) cout << lis[i] << " ";
    
    return 0;
}
