#include <iostream>
#include <vector>

using namespace std;

int n, num_queries;
vector<vector<int>> cow_count, p_sum;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> num_queries;
    
    cow_count.assign(3, vector<int>(n, 0));
    p_sum.assign(3, vector<int>(n+1, 0));
    int cow;
    for (int i = 0; i < n; i++) {
        cin >> cow;
        ++cow_count[cow - 1][i];
        for (int j = 0; j < 3; j++) {
            p_sum[j][i + 1] = p_sum[j][i] + cow_count[j][i];
        }
    }
    
    int left, right;
    for (int q = 0; q < num_queries; q++) {
        cin >> left >> right;
        for (int i = 0; i < 3; i++) {
            cout << p_sum[i][right] - p_sum[i][left - 1] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
