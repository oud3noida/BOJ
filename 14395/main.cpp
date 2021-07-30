#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int MAX = 1'000'000'000;
constexpr char OPS[3] = {'*', '+', '/'};
int destination;
vector<bool> visited;
queue<pair<pair<int, string>, int>> q;

long long calculate(long long x, char op) {
    switch (op) {
        case '*': return x*x;
        case '+': return x<<1;
        case '/': return 1;
    }
    
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    visited.assign(MAX + 1, false);
    
    int cur;
    cin >> cur >> destination;
    
    if (cur == destination) {
        cout << 0;
        return 0;
    }
    
    q.emplace(make_pair(cur, ""), 0);
    visited[cur] = true;
    
    while (!q.empty()) {
        cur = q.front().first.first;
        string operators = q.front().first.second;
        int num_operations = q.front().second;
        q.pop();
        
        if (cur == destination) {
            cout << operators;
            return 0;
        }
        
        for (char op : OPS) {
            long long next = calculate(cur, op);
            if (next > MAX || visited[next]) continue;
            
            q.emplace(make_pair(next, operators+op), num_operations+1);
            visited[next] = true;
        }
    }
    
    cout << -1;
    
    return 0;
}
