#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

map<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>
    processes_by_priority;

int execute_process() {
    auto cur = processes_by_priority.rbegin();
    auto [id, t] = (cur->second).top();
    (cur->second).pop();
    
    if (t-1 > 0) {
        processes_by_priority[(cur->first) - 1].emplace(id, t-1);
    }
    
    if ((cur->second).empty()) {
        processes_by_priority.erase(cur->first);
    }
    
    return id;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, end_time, id, t, priority;
    
    cin >> end_time >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> id >> t >> priority;
        processes_by_priority[priority].emplace(id, t);
    }
    
    for (int i = 0; i < end_time; i++) {
        cout << execute_process() << '\n';
    }
    
    return 0;
}
