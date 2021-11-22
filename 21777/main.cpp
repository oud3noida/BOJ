#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n;
vector<int> record;
map<int, pair<int, int>> processes;

void interpret_record() {
    int priority = 1;
    for (int i = n - 1; i >= 0; i--) {
        auto [p_begin, p_end] = processes[record[i]];
        processes[record[i]] = make_pair(p_begin == 0 ? priority : p_begin, priority);
        if (i > 0 && record[i - 1] >= record[i]) {
            priority++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    record.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> record[i];
    }
    
    interpret_record();
    
    cout << processes.size() << '\n';
    for (auto p : processes) {
        cout << p.first << ' ';
        auto [p_begin, p_end] = p.second;
        cout << (p_end - p_begin + 1) << ' ' << p_end + 1 << '\n';
    }
    
    return 0;
}
