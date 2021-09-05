#include <iostream>
#include <vector>

using namespace std;

constexpr int DAYS = 7;

int n;
vector<vector<int>> teams;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    teams.assign(DAYS + 1, vector<int>());
    teams[0].push_back(n);
    
    for (int day = 1; day <= DAYS; ++day) {
        for (int k : teams[day - 1]) {
            if (k != 1) teams[day].push_back(k/2);
            teams[day].push_back(k - k/2);
        }
        
        bool is_in_team_a = true;
        for (int k : teams[day]) {
            for (int i = 0; i < k; ++i) {
                cout << (is_in_team_a ? 'A' : 'B');
            }
            is_in_team_a = !is_in_team_a;
        }
        
        cout << '\n';
    }
    
    return 0;
}
