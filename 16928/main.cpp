#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int num_ladder, num_snake;
vector<bool> visited;
vector<int> connected;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    visited.assign(101, false);
    connected.assign(101, 0);
    for (int i=1; i<=100; ++i)
        connected[i] = i;
    
    cin >> num_ladder >> num_snake;
    
    int start, end;
    for (int i=0; i<(num_ladder+num_snake); ++i) {
        cin >> start >> end;
        connected[start] = end;
    }
    
    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));
    visited[1] = true;
    
    while (!q.empty()) {
        int cur = q.front().first;
        int num_rolls = q.front().second;
        q.pop();
        
        if (cur == 100) {
            cout << num_rolls;
            break;
        }
        
        for (int i=1; i<=6; ++i) {
            int next = connected[cur+i];
            if (!visited[next]) {
                visited[next] = true;
                q.push(make_pair(next, num_rolls+1));
            }
        }
    }
    
    return 0;
}
