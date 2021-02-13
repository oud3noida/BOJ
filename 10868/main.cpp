#include <iostream>
#include <vector>

using namespace std;

const int INF = 1'999'999'999;

class MinFenwickTree {
private:
    int tree_size;
    vector<int> real, tree1, tree2;
    enum TreeType {Tree1, Tree2};

    bool in_range(int index) {
        return 0 < index && index <= tree_size;
    }

    int parent(int i, TreeType tree_type) {
        if (tree_type == Tree1)
            return i + (i & ~(i - 1));
        else
            return i - (i & ~(i - 1));
    }

public:
    MinFenwickTree(vector<int> &data)
    : tree_size(data.size()), real(data) {
        tree1.assign(tree_size + 1, INF);
        tree2.assign(tree_size + 1, INF);

        for (int i = 1; i <= tree_size; ++i) {
            tree1[i] = min(tree1[i], real[i - 1]);

            int parent_index = parent(i, Tree1);
            if (in_range(parent_index))
                tree1[parent_index] = min(tree1[parent_index], tree1[i]);
        }

        for (int i = tree_size; i >= 1; --i) {
            tree2[i] = min(tree2[i], real[i - 1]);

            int parent_index = parent(i, Tree2);
            if (in_range(parent_index))
                tree2[parent_index] = min(tree2[parent_index], tree2[i]);
        }
    }

    int query(int begin, int end) {
        int ret = INF;

        int i = begin;
        while (parent(i, Tree1) <= end) {
            ret = min(ret, tree2[i]);
            i = parent(i, Tree1);
        }

        i = end;
        while (parent(i, Tree2) >= begin) {
            ret = min(ret, tree1[i]);
            i = parent(i, Tree2);
        }

        ret = min(ret, real[i - 1]);
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, num_queries;
    cin >> N >> num_queries;

    vector<int> arr(N, INF);
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    auto tree = new MinFenwickTree(arr);

    int begin, end;
    for (int i = 0; i < num_queries; ++i) {
        cin >> begin >> end;
        cout << tree->query(begin, end) << '\n';
    }

    return 0;
}