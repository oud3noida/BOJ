#include <iostream>
#include <vector>

using namespace std;

int N;
long long num_d, num_g;
vector<pair<int, int>> edges;
vector<int> num_edge;

long long find_d(int a, int b) {
    return (long long) (num_edge[a] - 1) * (num_edge[b] - 1);
}

long long find_g(int cur) {
    if (num_edge[cur] < 3) return 0;
    return (long long) num_edge[cur] * (num_edge[cur] - 1) * (num_edge[cur] - 2) / 6;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    num_edge.assign(N, 0);

    int a, b;
    for (int i=0; i<N-1; ++i) {
        cin >> a >> b;
        edges.emplace_back(a-1, b-1);
        ++num_edge[a-1];
        ++num_edge[b-1];
    }

    num_d = 0;
    for (auto edge : edges)
        num_d += find_d(edge.first, edge.second);

    num_g = 0;
    for (int vertex=0; vertex<N; ++vertex)
        num_g += find_g(vertex);

    if (num_d > 3*num_g) cout << 'D';
    else if (num_d < 3*num_g) cout << 'G';
    else cout << "DUDUDUNGA";

    return 0;
}