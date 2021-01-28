#include <iostream>
#include <vector>

using namespace std;

int num_bulb, num_press;
vector<bool> bulbs;

void press_switch_adj(int cur) {
    ++num_press;
    if (cur > 0) bulbs[cur-1] = !bulbs[cur-1];
    bulbs[cur] = !bulbs[cur];
    if (cur < num_bulb-1) bulbs[cur+1] = !bulbs[cur+1];
}

bool press_switch(int cur) {
    if (cur == num_bulb - 1) {
        if (bulbs[cur-1] != bulbs[cur]) return false;
        if (!bulbs[cur-1]) press_switch_adj(cur);
        return true;
    }

    if (cur == 0 || !bulbs[cur-1]) press_switch_adj(cur);
    return press_switch(cur+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_bulb;

    vector<char> initial_bulbs;
    initial_bulbs.resize(num_bulb);
    bulbs.resize(num_bulb);
    for (int i=0; i<num_bulb; ++i) cin >> initial_bulbs[i];

    char c;
    for (int i=0; i<num_bulb; ++i) {
        cin >> c;
        bulbs[i] = (c == initial_bulbs[i]);
    }

    vector<bool> tmp_bulbs(bulbs);
    num_press = 0;
    if (press_switch(1)) cout << num_press;
    else {
        num_press = 0;
        bulbs = tmp_bulbs;
        if (press_switch(0)) cout << num_press;
        else cout << -1;
    }

    return 0;
}