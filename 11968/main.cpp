#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int n;
vector<int> elsie_cards;
deque<int> bessie_cards;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    elsie_cards.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> elsie_cards[i];
    }
    sort(elsie_cards.begin(), elsie_cards.end());
    
    int i = 0;
    for (int x = 1; x <= 2*n; x++) {
        if (elsie_cards[i] == x) ++i;
        else bessie_cards.push_back(x);
    }
    
    int ans = 0;
    for (auto card = elsie_cards.rbegin(); card != elsie_cards.rend(); ++card) {
        if (bessie_cards.back() > *card) {
            bessie_cards.pop_back();
            ++ans;
        } else {
            bessie_cards.pop_front();
        }
    }
    
    cout << ans;
    
    return 0;
}
