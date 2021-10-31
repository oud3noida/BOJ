#include <iostream>
#include <list>
#include <cassert>

using namespace std;

constexpr int LOG_MAX = 19, MOD = 1'000'000'007;
int n;
list<int> operands, operators;
list<int>::iterator top;

int inverse(int x) {
    int r0 = x, r1 = MOD,
            s0 = 1, s1 = 0,
            t0 = 0, t1 = 1,
            tmp = 0, q = 0;

    while (r1 != 0) {
        q = r0 / r1;

        tmp = r0 - r1*q;
        r0 = r1;
        r1 = tmp;

        tmp = s0 - s1*q;
        s0 = s1;
        s1 = tmp;

        tmp = t0 - t1*q;
        t0 = t1;
        t1 = tmp;
    }

    return (s0 + MOD) % MOD;
}

struct Node {
    int num_child;
    Node *left, *right;
    list<int>::iterator it;
    
    Node(list<int> &l, int depth) {
        num_child = 0;
        if (depth < LOG_MAX) {
            left = new Node(l, depth + 1);
            right = new Node(l, depth + 1);
            num_child += left->num_child + right->num_child;
        } else if (top != l.end()) {
            num_child = 1;
            it = top++;
        } else {
            it = l.end();
        }
    }
    
    list<int>::iterator pop(int index) {
        if (left == nullptr) {
            return it;
        }
        
        if (index <= left->num_child) {
            --(left->num_child);
            return left->pop(index);
        } else {
            --(right->num_child);
            return right->pop(index - left->num_child);
        }
    }
    
    Node* find(int index) {
        if (left == nullptr) {
            return this;
        }
        
        if (index <= left->num_child) {
            return left->find(index);
        } else {
            return right->find(index - left->num_child);
        }
    }
};

Node *operands_tree, *operators_tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    for (int i = 0; i < 2*n - 1; ++i) {
        if (i % 2 == 0) {
            int x;
            cin >> x;
            operands.push_back(x);
        } else {
            char c;
            cin >> c;
            operators.push_back(c);
        }
    }
    
    top = operands.begin();
    operands_tree = new Node(operands, 0);
    top = operators.begin();
    operators_tree = new Node(operators, 0);
    
    int v = 0;
    for (int q = 0; q < n-1; ++q) {
        int u;
        cin >> u;
        u = u ^ v;
        
        auto lhs = operands_tree->pop(u);
        auto rhs_raw = operands_tree->find(u);
        auto rhs = rhs_raw->it;
        auto op = operators_tree->pop(u);
        
        switch (*op) {
            case '+':
                v = ((long long) (*lhs) + (*rhs)) % MOD;
                break;
            case '-':
                v = ((long long) (*lhs) - (*rhs) + MOD) % MOD;
                break;
            case '*':
                v = ((long long) (*lhs) * (*rhs)) % MOD;
                break;
            case '/':
                v = ((long long) (*lhs) * inverse(*rhs)) % MOD;
                break;
        }
        
        *rhs = v;
        
        cout << v << '\n';
    }
    
    return 0;
}
