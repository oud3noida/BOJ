#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n;
vector<vector<int>> cities;

int str_to_int(string s) {
    return (s[0] - 'A') * 26 + (s[1] - 'A');
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    cities.assign(26*26, vector<int>(26*26, 0));
    string city, state;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> city >> state;
        int city_index = str_to_int(city);
        int state_index = str_to_int(state);
        
        ++cities[city_index][state_index];
    }
    
    for (int i = 0; i < 26*26; i++) {
        for (int j = i+1; j < 26*26; j++) {
            ans += cities[i][j] * cities[j][i];
        }
    }
    
    cout << ans;
    
    return 0;
}
