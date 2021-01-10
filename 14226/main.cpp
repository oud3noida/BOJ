#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Data {
    int num_emotes, time_spent;
    Data(int num_emotes, int time_spent) :
        num_emotes(num_emotes), time_spent(time_spent) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    auto cmp = [](Data a, Data b){return a.time_spent > b.time_spent;};
    priority_queue<Data, vector<Data>, decltype(cmp)> q(cmp);
    vector<bool> visited(2000, false);

    q.emplace(1, 0);

    while (!q.empty()) {
        int cur_num = q.top().num_emotes,
            cur_time = q.top().time_spent;
        q.pop();
        if (visited[cur_num]) continue;
        visited[cur_num] = true;

        if (cur_num == S) {
            cout << cur_time;
            return 0;
        }

        if (cur_num > 1) q.emplace(cur_num - 1, cur_time + 1);

        int i = 1;
        while (cur_num * (++i) < 2000) q.emplace(cur_num * i, cur_time + i);
    }

    return 0;
}