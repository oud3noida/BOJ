#include <iostream>
#include <vector>

using namespace std;

int l, n, speed_john, speed_bessie;
vector<pair<int, int>> possible_stops, actual_stops;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> l >> n >> speed_john >> speed_bessie;
    
    int x, c;
    for (int i = 0; i < n; i++) {
        cin >> x >> c;
        possible_stops.emplace_back(x, c);
    }
    
    int max_grass = 0;
    for (int i = n-1; i >= 0; i--) {
        if (max_grass < possible_stops[i].second) {
            max_grass = possible_stops[i].second;
            actual_stops.push_back(possible_stops[i]);
        }
    }
    
    int prev_pos = 0;
    long long ans = 0;
    for (int i = actual_stops.size()-1; i >= 0; i--) {
        auto [pos, grass] = actual_stops[i];
        long long d_pos = pos - prev_pos;
        ans += d_pos * (speed_john - speed_bessie) * grass;
        prev_pos = pos;
    }
    
    cout << ans;
    
    return 0;
}
