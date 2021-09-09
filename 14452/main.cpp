#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, t_max;
vector<int> cows;

int performance_time(int k) {
    priority_queue<int, vector<int>, greater<int>> stage;
    for (int i = 0; i < k; i++) {
        stage.push(cows[i]);
    }
    
    for (int i = k; i < n; i++) {
        int finished = stage.top();
        stage.pop();
        stage.push(finished + cows[i]);
    }
    
    for (int i = 0; i < k-1; i++) {
        stage.pop();
    }
    
    return stage.top();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> t_max;
    
    cows.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    
    int left = 1;
    int right = n;
    while (left < right) {
        int mid = (left + right) / 2;
        if (performance_time(mid) <= t_max) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    cout << left;
    
    return 0;
}
