#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_cards, num_queries;
vector<int> cards;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_cards;
    
    cards.assign(num_cards, 0);
    for (int i=0; i<num_cards; ++i) {
        cin >> cards[i];
    }
    sort(cards.begin(), cards.end());
    
    cin >> num_queries;
    
    int query;
    for (int q=0; q<num_queries; ++q) {
        cin >> query;
        cout << (binary_search(cards.begin(), cards.end(), query) ? 1 : 0) << ' ';
    }
    
    return 0;
}
