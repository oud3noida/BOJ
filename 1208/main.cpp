#include <iostream>
#include <vector>

using namespace std;

const int ZERO = 2'000'000;
vector<long long> count;
int n, target;
long long answer;
vector<int> sequence;

void traverse_left_half(int cur, int sum) {
    if (cur == n/2) {
        ++count[sum + ZERO];
        return;
    }
    
    traverse_left_half(cur+1, sum);
    traverse_left_half(cur+1, sum + sequence[cur]);
}

void traverse_right_half(int cur, int sum) {
    if (cur == n) {
        int x = target - sum + ZERO;
        if (0 <= x && x <= 2*ZERO)
            answer += count[target - sum + ZERO];
        return;
    }
    
    traverse_right_half(cur+1, sum);
    traverse_right_half(cur+1, sum + sequence[cur]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    count.assign(ZERO*2+1, 0);
    answer = 0;
    
    cin >> n >> target;
    sequence.assign(n, 0);
    
    for (int i=0; i<n; ++i)
        cin >> sequence[i];
    
    traverse_left_half(0, 0);
    traverse_right_half(n/2, 0);
    
    cout << answer - (target == 0 ? 1 : 0);
    
    return 0;
}
