#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> sequence;

long long num_inversions(int left, int right) {
    if (left == right) return 0;
    
    vector<int> sorted_sequence;
    int mid = (left + right) / 2;
    
    long long num_inversions_left = num_inversions(left, mid),
              num_inversions_right = num_inversions(mid+1, right),
              num_inversions_merge = 0;
    
    int left_index = left,
        right_index = mid+1;
    
    while (left_index <= mid || right_index <= right) {
        if (left_index > mid) {
            sorted_sequence.push_back(sequence[right_index++]);
        } else if (right_index > right) {
            sorted_sequence.push_back(sequence[left_index++]);
        } else if (sequence[left_index] <= sequence[right_index]) {
            sorted_sequence.push_back(sequence[left_index++]);
        } else {
            num_inversions_merge += (mid - left_index + 1);
            sorted_sequence.push_back(sequence[right_index++]);
        }
    }
    
    for (int i = 0; i <= right - left; ++i) {
        sequence[left + i] = sorted_sequence[i];
    }
    
    return num_inversions_left + num_inversions_right + num_inversions_merge;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    cin >> n;
    
    sequence.assign(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> sequence[i];
    }
    
    cout << num_inversions(0, n-1);
    
    return 0;
}
