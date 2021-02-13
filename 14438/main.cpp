#include <iostream>
#include <vector>

using namespace std;

const int INF = 1'999'999'999;

class MinSegTree {
private:
    int range_begin, range_end, range_mid;
    MinSegTree *left_child, *right_child;
    int value;

public:
    MinSegTree(int begin, int end, const vector<int> &data)
            : range_begin(begin), range_end(end), range_mid((begin + end) / 2) {
        if (range_begin == range_end) {
            value = data[range_begin];
            return;
        }

        left_child = new MinSegTree(range_begin, range_mid, data);
        right_child = new MinSegTree(range_mid + 1, range_end, data);
        value = min(left_child->value, right_child->value);
    }

    int query(int begin, int end) {
        if (begin == range_begin && end == range_end) {
            return value;
        }

        int left_value = INF, right_value = INF;
        if (begin <= range_mid)
            left_value = left_child->query(begin, min(range_mid, end));
        if (end > range_mid)
            right_value = right_child->query(max(range_mid + 1, begin), end);
        return min(left_value, right_value);
    }

    void update(int index, int new_value) {
        if (index == range_begin && index == range_end) {
            value = new_value;
        } else if (index <= range_mid) {
            left_child->update(index, new_value);
            value = min(left_child->value, right_child->value);
        } else {
            right_child->update(index, new_value);
            value = min(left_child->value, right_child->value);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> arr(N, INF);
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    auto tree = new MinSegTree(0, N - 1, arr);

    int num_queries;
    cin >> num_queries;

    int command_type, a, b;
    for (int i = 0; i < num_queries; ++i) {
        cin >> command_type >> a >> b;
        if (command_type == 1)
            tree->update(a-1, b);
        else
            cout << tree->query(a-1, b-1) << '\n';
    }

    return 0;
}