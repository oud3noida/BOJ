#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> rooms;

int gcd_two(int a, int b) {
    if (a%b == 0) return b;
    return gcd_two(b, a%b);
}

int gcd_range(int left, int right) {
    int length = right - left + 1;
    if (length == 1) return rooms[left];
    return gcd_two(rooms[left], gcd_range(left+1, right));
}

int beauty(int left, int right) {
    int length = right - left + 1;
    if (length == 1) return rooms[left];
    
    int mid = left + length/2 - 1;
    int choose_left = gcd_range(left, mid) + beauty(mid+1, right),
        choose_right = beauty(left, mid) + gcd_range(mid+1, right);

    return max(choose_left, choose_right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    rooms.assign(n, 0);
    
    for (int i=0; i<n; ++i)
        cin >> rooms[i];
    
    cout << beauty(0, n-1);
    
    return 0;
}
