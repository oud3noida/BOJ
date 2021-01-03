#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1'000'000'007;
int N, Q, num_set;
vector<vector<long long>> cache;
vector<long long> ans;
vector<int> parent, prior;

long long partition_of_set(int n, int k) {
    if (k == 1 || k == n) return 1;
    long long& ret = cache[n][k];
    if (ret != -1) return ret;
    ret = partition_of_set(n-1, k-1) % MOD;
    ret += (k * partition_of_set(n-1, k)) % MOD;
    ret %= MOD;
    return ret;
}

long long sum_of_partition_of_set(int n) {
    long long& ret = ans[n];
    if (ret != -1) return ret;
    ret = 0;
    for (int k=1; k<=n; ++k) {
        ret += partition_of_set(n, k);
        ret %= MOD;
    }
    return ret;
}

int find(int x) {
    if (parent[x] != x) return parent[x] = find(parent[x]);
    return x;
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (prior[a] >= prior[b]) {
        ++prior[a];
        parent[b] = a;
    } else {
        ++prior[b];
        parent[a] = b;
    }
    --num_set;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    cache.assign(N+1, vector<long long>(N+1, -1));
    ans.assign(N+1, -1);
    for (int i=0; i<N; ++i) parent.push_back(i);
    prior.assign(N, 0);
    num_set = N;

    int a, b;
    for (int q=0; q < Q; ++q) {
        cin >> a >> b;
        merge(a-1, b-1);
        cout << sum_of_partition_of_set(num_set) << "\n";
    }

    return 0;
}