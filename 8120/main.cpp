#include <iostream>
#include <vector>
#include <stack>

using namespace std;

constexpr double EPSILON = 0.00003;
int n;

struct Tree {
    double code_value;
    int real_value;
    Tree *left_child, *right_child;
    bool occupied;
    int lazy;
    
    Tree(int left, int right) 
        : code_value(n - (left + right) / 2),
          real_value((left + right) / 2),
          occupied(false), lazy(0) {
        
        int mid = (left + right) / 2;
        
        if (left != mid) {
            left_child = new Tree(left, mid-1);
        }
        
        if (mid != right) {
            right_child = new Tree(mid+1, right);
        }
    }
    
    void update() {
        if (lazy == 0) return;
        
        if (left_child != nullptr) {
            left_child->lazy += lazy;
        }
        if (right_child != nullptr) {
            right_child->lazy += lazy;
        }
        
        code_value -= lazy;
        lazy = 0;
    }
    
    int find_real(double code) {
        update();
        
        if (abs(code - code_value) < EPSILON && !occupied) {
            occupied = true;
            code_value -= (real_value) / (n + 1.0);
            if (left_child != nullptr) {
                left_child->lazy += 1;
            }
            return real_value;
        }
        
        int ret = -1;
        
        if (code - code_value < EPSILON) {
            if (right_child != nullptr) {
                ret = right_child->find_real(code);
            }
            
            if (ret != -1) {
                code_value -= 1;
                if (left_child != nullptr) {
                    left_child->lazy += 1;
                }
            }
        } else if (code - code_value > EPSILON) {
            if (left_child != nullptr) {
                ret = left_child->find_real(code);
            }
        }
        if (ret == -1) return -1;
        return ret;
    }
};

vector<int> codes;
stack<int> reals;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    codes.assign(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> codes[i];
    }
    
    Tree* tree = new Tree(1, n);
    
    for (int i=n-1; i>=0; --i) {
        int real = tree->find_real(codes[i]);
        if (real == -1) {
            cout << "NIE";
            return 0;
        }
        reals.push(real);
    }
    
    while (!reals.empty()) {
        cout << reals.top() << '\n';
        reals.pop();
    }
    
    return 0;
}
