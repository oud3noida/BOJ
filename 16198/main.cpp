#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> energy_orbs;

int max_energy(int num_orbs) {
    if (num_orbs == 2) return 0;
    
    int ret = 0;
    for (auto it=++energy_orbs.begin(); it!=--energy_orbs.end(); ++it) {
        int tmp = *it;
        
        int cur_energy = (*(it - 1)) * (*(it + 1));
        energy_orbs.erase(it);
        
        ret = max(ret, max_energy(num_orbs-1) + cur_energy);
        
        energy_orbs.insert(it, tmp);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    energy_orbs.assign(n, 0);
    
    for (int i=0; i<n; ++i) {
        cin >> energy_orbs[i];
    }
    
    cout << max_energy(n);

    return 0;
}
