#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_a, num_b;
vector<int> a, b;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_a >> num_b;
    
    a.assign(num_a, 0);
    b.assign(num_b, 0);
    for (int i=0; i<num_a; ++i) {
        cin >> a[i];
    }
    for (int i=0; i<num_b; ++i) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    auto it_a = a.begin();
    auto it_b = b.begin();
    while (it_a != a.end() || it_b != b.end()) {
        if (it_b == b.end() || (it_a != a.end() && *it_a < *it_b)) {
            cout << *it_a << ' ';
            ++it_a;
        }
        else if (it_a == a.end() || (it_b != b.end() && *it_a >= *it_b)) {
            cout << *it_b << ' ';
            ++it_b;
        }
    }
    
    return 0;
}
