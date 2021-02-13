#include <iostream>
#include <vector>

using namespace std;

const int INF = 1'987'654'321;
vector<int> values;

class TreeNode {
private:
    TreeNode *left_child, *right_child;
    int range_begin, range_end, range_mid;
    int value;

public:
    TreeNode(int begin, int end)
    : range_begin(begin), range_end(end), range_mid((begin + end) / 2), value(INF) {
        if (begin == end) {
            value = values[begin];
            return;
        }

        left_child = new TreeNode(range_begin, range_mid);
        right_child = new TreeNode(range_mid + 1, range_end);
        value = min(left_child->value, right_child->value);
    }

    int query_range(int query_begin, int query_end) {
        if (query_begin == range_begin && query_end == range_end) {
            return value;
        }

        int left_min = INF, right_min = INF;
        if (query_begin <= range_mid)
            left_min = left_child->query_range(query_begin, min(query_end, range_mid));
        if (query_end > range_mid)
            right_min = right_child->query_range(max(query_begin, range_mid + 1), query_end);
        return min(left_min, right_min);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_values, num_queries;
    cin >> num_values >> num_queries;

    values.resize(num_values);
    for (int i = 0; i < num_values; ++i) {
        cin >> values[i];
    }

    auto *root = new TreeNode(0, num_values - 1);

    int begin, end;
    for (int i = 0; i < num_queries; ++i) {
        cin >> begin >> end;
        cout << root->query_range(begin - 1, end - 1) << '\n';
    }

    return 0;
}