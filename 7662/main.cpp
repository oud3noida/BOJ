#include <iostream>
#include <set>

using namespace std;

int k, n;
char c;
multiset<int> q;

void calc(bool insert, int x) {
    if (insert) q.insert(x);
    else if (!q.empty()) {
        if (x == -1) q.erase(q.begin());        // Delete minimum
        else if (x == 1) q.erase(--q.end());    // Delete maximum
    }
}

int main()
{
    // For faster input
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t=0; t<T; t++) {
        cin >> k;
        q.clear();
        for (int i=0; i<k; i++) {
            cin >> c >> n;
            calc(c == 'I', n);
        }
        if (q.empty()) cout << "EMPTY\n";
        else cout << *(--q.end()) << " " << *(q.begin()) << "\n";
    }

    return 0;
}
