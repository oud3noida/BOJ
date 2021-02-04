#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_computers, num_connections, num_disjoint_sets;
vector<int> parent, merge_rank;

int find(int x) {
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (merge_rank[a] > merge_rank[b]) {
        parent[b] = a;
        ++merge_rank[a];
    } else {
        parent[a] = b;
        ++merge_rank[b];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_computers >> num_connections;

    vector<pair<int, pair<int, int>>> connections;

    int computer1, computer2, cost;
    for (int i = 0; i < num_connections; ++i) {
        cin >> computer1 >> computer2 >> cost;
        if (computer1 != computer2) {
            auto connected_computers = make_pair(computer1 - 1, computer2 - 1);
            connections.emplace_back(cost, connected_computers);
        }
    }
    sort(connections.begin(), connections.end());

    num_disjoint_sets = num_computers;
    parent.reserve(num_computers);
    merge_rank.assign(num_computers, 0);
    for (int i = 0; i < num_computers; ++i)
        parent.push_back(i);

    int min_cost = 0;
    auto cur_connection = connections.begin();
    while (num_disjoint_sets > 1) {
        auto cur_computers = cur_connection->second;
        int cur_cost = cur_connection->first,
            cur_computer1 = cur_computers.first,
            cur_computer2 = cur_computers.second;
        if (find(cur_computer1) != find(cur_computer2)) {
            merge(cur_computer1, cur_computer2);
            min_cost += cur_cost;
            --num_disjoint_sets;
        }
        ++cur_connection;
    }

    cout << min_cost;

    return 0;
}