#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_house, num_router;
    cin >> num_house >> num_router;

    vector<int> houses(num_house, 0);
    for (int i = 0; i < num_house; ++i)
        cin >> houses[i];
    sort(houses.begin(), houses.end());

    int left = 0, right = houses.back() - houses.front() + 1;
    while (left + 1 < right) {
        int cur_distance = (left + right) / 2;
        int cur_house_pos = houses.front();
        bool distance_too_far = false;

        for (int i = 0; i < num_router-1; ++i) {
            int next_house_pos = cur_house_pos + cur_distance;
            auto next_house = lower_bound(houses.begin(), houses.end(), next_house_pos);
            if (next_house == houses.end()) {
                distance_too_far = true;
                break;
            } else {
                cur_house_pos = *next_house;
            }
        }

        if (distance_too_far)
            right = cur_distance;
        else
            left = cur_distance;
    }

    cout << left;

    return 0;
}