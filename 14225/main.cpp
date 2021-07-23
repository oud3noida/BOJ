#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100'000;
int n;
vector<int> sequence;
vector<bool> visited;

void sum_of_subsequence(int cur, int cur_sum) {
    if (cur == n) {
        visited[cur_sum] = true;
        return;
    }
    
    sum_of_subsequence(cur+1, cur_sum);
    sum_of_subsequence(cur+1, cur_sum + sequence[cur]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    visited.assign(n*MAX+1, false);
    
    int x;
    for (int i=0; i<n; ++i) {
        cin >> x;
        sequence.emplace_back(x);
    }
    
    sum_of_subsequence(0, 0);
    
    for (int i=1; i<n*MAX+1; ++i) {
        if (!visited[i]) {
            cout << i;
            break;
        }
    }
    
    return 0;
}
