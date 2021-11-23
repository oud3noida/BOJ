#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

struct Process {
    long long id, p_begin, p_end;
    
    Process(long long id, long long p_begin, long long p_end)
    : id(id), p_begin(p_begin), p_end(p_end) {}
};

vector<Process> process_list;
map<long long, long long> num_process_by_priority, priority_at_time;

void calculate_priority_at_time() {
    long long sum_t = 0LL;
    for (auto it = num_process_by_priority.rbegin();
         it != prev(num_process_by_priority.rend()); it++) {
        long long t = it->second * abs(it->first - next(it)->first);
        
        if (t == 0LL) continue;
        
        sum_t += t;
        priority_at_time[sum_t] = it->first;
    }
}

long long query_id(long long t) {
    auto it = priority_at_time.lower_bound(t);
    long long priority_value = it->second;
    long long prev_t = 0LL;
    if (it != priority_at_time.begin()) {
        prev_t = prev(it)->first;
    }
    
    vector<long long> candidates;
    for (auto process : process_list) {
        if (process.p_begin >= priority_value && priority_value > process.p_end) {
            candidates.push_back(process.id);
        }
    }
    
    return candidates[(t - prev_t - 1LL) % candidates.size()];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, num_queries;
    long long id, t, priority;
    
    cin >> num_queries >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> id >> t >> priority;
        long long p_begin = priority;
        long long p_end = priority - t;
        
        process_list.emplace_back(id, p_begin, p_end);
        
        // Mark the beginning and the end of the process by priority
        num_process_by_priority[p_begin]++;
        num_process_by_priority[p_end]--;
    }
    sort(process_list.begin(), process_list.end(),
         [](const Process& a, const Process& b) { return a.id < b.id; }
        );
    
    // Calculate the number of process by priority, using prefix sum
    // e.g. [1, 2, 1, -1, -3] => [1, 3, 4, 3, 0]
    for (auto it = next(num_process_by_priority.rbegin());
         it != num_process_by_priority.rend(); it++) {
        it->second += prev(it)->second;
    }
    
    calculate_priority_at_time();
    
    for (int i = 0; i < num_queries; i++) {
        cin >> t;
        cout << query_id(t) << '\n';
    }
    
    return 0;
}
