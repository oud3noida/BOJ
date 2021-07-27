#include <iostream>
#include <vector>

using namespace std;

int L, range, damage, claymore, usedClaymore, curZombie;
vector<int> positionUsedClaymore;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> range >> damage >> claymore;
    
    usedClaymore = 0;
    for (int i=0; i<L; ++i) {
        cin >> curZombie;
        auto a = positionUsedClaymore.begin(),
             b = positionUsedClaymore.end();
        int numNotShot = b - lower_bound(a, b, i - range + 1);
        curZombie -= damage * (min(range, i+1) - numNotShot);
        if (curZombie > 0) {
            ++usedClaymore;
            positionUsedClaymore.push_back(i);
        }
        if (usedClaymore > claymore) {
            cout << "NO";
            return 0;
        }
    }
    
    cout << "YES";
    
    return 0;
}
