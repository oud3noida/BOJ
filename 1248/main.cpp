#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<char>> unary_p_sum;
vector<int> unary, ans;

int unary2int(char c) {
    switch (c) {
        case '+': return 1;
        case '-': return -1;
        default: return 0;
    }
}

bool check_unary(char c, int x) {
    switch (c) {
        case '+': return x > 0;
        case '-': return x < 0;
        default: return x == 0;
    }
}

bool check_ans(int cur) {
    int p_sum = ans[cur];
    for (int prev=cur-1; prev>=0; --prev) {
        p_sum += ans[prev];
        if (!check_unary(unary_p_sum[prev][cur], p_sum)) return false;
    }
    return true;
}

bool find_ans(int cur) {
    if (cur == n) return true;
    if (unary[cur] == 0) return find_ans(cur+1);

    for (int i=1; i<=10; ++i) {
        ans[cur] = i * unary[cur];
        if (check_ans(cur) && find_ans(cur+1)) return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    unary_p_sum.assign(n, vector<char>(n, '?'));
    unary.assign(n, 0);
    for (int i=0; i<n; ++i) {
        for (int j=i; j<n; ++j) {
            cin >> unary_p_sum[i][j];
            if (i == j) unary[i] = unary2int(unary_p_sum[i][j]);
        }
    }

    ans.assign(n, 0);
    find_ans(0);

    for (int i=0; i<n; ++i) cout << ans[i] << " ";

    return 0;
}