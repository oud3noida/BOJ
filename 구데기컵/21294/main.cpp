#include <iostream>

using namespace std;

int num_queries;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_queries;
    
    int a;
    for (int i=0; i<num_queries; ++i) {
        cin >> a;
        if (a == 2) cout << '\n';
    }
    
    return 0;
}
