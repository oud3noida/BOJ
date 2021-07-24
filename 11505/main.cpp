#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1'000'000'007;
int n, num_queries, a, b, c;
vector<long long> sequence;

class Segment_Tree {
private:
    int range_begin, range_end, range_mid;
    Segment_Tree *left_child, *right_child;
    long long value;

public:
    Segment_Tree(int begin, int end, const vector<long long> &data)
    : range_begin(begin), range_end(end), range_mid((begin + end) / 2) {
        if (range_begin == range_end) {
            value = data[range_begin] % MOD;
            return;
        }

        left_child = new Segment_Tree(range_begin, range_mid, data);
        right_child = new Segment_Tree(range_mid + 1, range_end, data);
        value = (left_child->value * right_child->value) % MOD;
    }

    long long query(int begin, int end) {
        if (begin == range_begin && end == range_end) {
            return value % MOD;
        }

        long long left_value = 1, right_value = 1;
        
        if (begin <= range_mid) {
            left_value = left_child->query(begin, min(range_mid, end));
            left_value %= MOD;
        }
        
        if (end > range_mid) {
            right_value = right_child->query(max(range_mid + 1, begin), end);
            right_value %= MOD;
        }
        
        return (left_value * right_value) % MOD;
    }

    void update(int index, int new_value) {
        if (index == range_begin && index == range_end) {
            value = new_value;
        } else if (index <= range_mid) {
            left_child->update(index, new_value);
            value = left_child->value * right_child->value;
        } else {
            right_child->update(index, new_value);
            value = left_child->value * right_child->value;
        }
        
        value %= MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;
    num_queries = a + b;

    sequence.assign(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> sequence[i];
    }
    auto tree = new Segment_Tree(0, n-1, sequence);

    for (int i=0; i<num_queries; ++i) {
        cin >> a >> b >> c;
        if (a == 1) tree->update(b-1, c);
        else cout << tree->query(b-1, c-1) % MOD << '\n';
    }

    return 0;
}
