#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
vector<int> cards, parent;

int find(int x) {
    if (cards[x] == parent[x]) return x;
    int root = find(x+1);
    parent[x] = parent[root];
    return root;
}

void visited(int a) {
    int root = find(a);
    parent[root] = cards[root+1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m >> k;
    
    int card;
    for (int i=0; i<m; ++i) {
        cin >> card;
        cards.push_back(card);
    }
    sort(cards.begin(), cards.end());
    
    for (int i=0; i<m; ++i) {
        parent.push_back(cards[i]);
    }
    
    for (int i=0; i<k; ++i) {
        cin >> card;
        int ans = upper_bound(parent.begin(), parent.end(), card) - parent.begin();
        cout << parent[find(ans)] << "\n";
        visited(ans);
    }
    
    return 0;
}
