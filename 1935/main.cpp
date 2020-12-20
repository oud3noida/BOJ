#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int char2num(char c) {
    return c - 'A';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> operands(n, 0);

    string expression;
    cin >> expression;
    for (int i=0; i<n; ++i) cin >> operands[i];

    stack<double> calc_stack;
    for (char c : expression) {
        double tmp;
        switch (c) {
            case '+':
                tmp = calc_stack.top(); calc_stack.pop();
                calc_stack.top() += tmp;
                break;
            case '-':
                tmp = calc_stack.top(); calc_stack.pop();
                calc_stack.top() -= tmp;
                break;
            case '*':
                tmp = calc_stack.top(); calc_stack.pop();
                calc_stack.top() *= tmp;
                break;
            case '/':
                tmp = calc_stack.top(); calc_stack.pop();
                calc_stack.top() /= tmp;
                break;
            default:
                calc_stack.push(operands[char2num(c)]);
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << calc_stack.top();

    return 0;
}