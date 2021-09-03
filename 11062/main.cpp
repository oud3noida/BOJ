#include <iostream>
#include <vector>

using namespace std;

int tests, n;
vector<int> cards;
vector<vector<int>> cache;

int score(int left, int right) {
    int is_to_maximize = (n - (right - left)) % 2;
    
    if (left == right) return cards[left] * is_to_maximize;
    
    int &ret = cache[left][right];
    if (ret != -1) return ret;
    
    int take_left = cards[left] * is_to_maximize + score(left + 1, right);
    int take_right = cards[right] * is_to_maximize + score(left, right - 1);
    
    ret = is_to_maximize ? max(take_left, take_right) : min(take_left, take_right);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    
    for (int t = 0; t < tests; t++) {
        cin >> n;
        
        cards.assign(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> cards[i];
        }
        
        cache.assign(n, vector<int>(n, -1));
        cout << score(0, n-1) << '\n';
    }
    
    return 0;
}
