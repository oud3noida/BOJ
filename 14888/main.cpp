#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1'999'999'999;
int N;
vector<int> operands, operators;

int calc_permutation() {
    int ret = operands[0];
    for (int i=0; i<N-1; ++i) {
        switch (operators[i]) {
            case 0:
                ret += operands[i + 1];
                break;
            case 1:
                ret -= operands[i + 1];
                break;
            case 2:
                ret *= operands[i + 1];
                break;
            case 3:
                ret /= operands[i + 1];
                break;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    operands.assign(N, 0);
    for (int i=0; i<N; ++i) cin >> operands[i];

    int num_cur_operators;
    for (int op=0; op<4; ++op) {
        cin >> num_cur_operators;
        for (int i=0; i<num_cur_operators; ++i)
            operators.push_back(op);
    }

    int min_ans = INF, max_ans = 0 - INF;
    do {
        int calc_result = calc_permutation();
        min_ans = min(min_ans, calc_result);
        max_ans = max(max_ans, calc_result);
    } while (next_permutation(operators.begin(), operators.end()));

    cout << max_ans << '\n' << min_ans;

    return 0;
}