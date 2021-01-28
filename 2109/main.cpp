#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10'000;
int num_request, sum_pay;
vector<int> schedule;
vector<pair<int, int>> requests;

int find_available_day(int day) {
    if (day == -1) return -1;
    if (day != schedule[day])
        schedule[day] = find_available_day(schedule[day]);
    return schedule[day];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    schedule.reserve(MAX);
    for (int i=0; i<MAX; ++i) schedule.push_back(i);

    cin >> num_request;

    requests.reserve(num_request);
    int pay, day;
    for (int i=0; i < num_request; ++i) {
        cin >> pay >> day;
        requests.emplace_back(pay, day-1);
    }
    sort(requests.begin(), requests.end());

    sum_pay = 0;
    for (auto req = requests.rbegin(); req != requests.rend(); ++req) {
        int available_day = find_available_day(req->second);
        if (available_day == -1) continue;
        --schedule[available_day];
        sum_pay += req->first;
    }

    cout << sum_pay;

    return 0;
}