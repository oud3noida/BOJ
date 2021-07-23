#include <iostream>
#include <vector>

using namespace std;

const int INF = 1'999'999'999;
int N;
int min_ans, max_ans;
vector<int> operands, operators;
vector<int> num_operators;

void calc_current_combination() {
    int calc_result = operands[0];
    for (int i=0; i<N-1; ++i) {
        switch (operators[i]) {
            case 0:
                calc_result += operands[i + 1];
                break;
            case 1:
                calc_result -= operands[i + 1];
                break;
            case 2:
                calc_result *= operands[i + 1];
                break;
            case 3:
                calc_result /= operands[i + 1];
                break;
        }
    }
    min_ans = min(min_ans, calc_result);
    max_ans = max(max_ans, calc_result);
}

void calc_all_combinations(int i) {
    if (i >= N-1) {
        calc_current_combination();
        return;
    }
    
    for (int op=0; op<4; ++op) {
        if (num_operators[op] > 0) {
            --num_operators[op];
            operators[i] = op;
            calc_all_combinations(i+1);
            ++num_operators[op];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    operands.assign(N, 0);
    for (int i=0; i<N; ++i) {
        cin >> operands[i];
    }

    operators.assign(N-1, 0);
    
    num_operators.assign(4, 0);
    for (int op=0; op<4; ++op) {
        cin >> num_operators[op];
    }
    
    min_ans = INF;
    max_ans = -INF;
    
    calc_all_combinations(0);
    
    cout << max_ans << '\n' << min_ans;

    return 0;
}
