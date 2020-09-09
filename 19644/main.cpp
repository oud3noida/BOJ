#include <iostream>

using namespace std;

int L, range, damage, claymore, usedClaymore, curZombie;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> range >> damage >> claymore;
    
    usedClaymore = 0;
    for (int i=0; i<L; ++i) {
        cin >> curZombie;
        curZombie -= damage * (min(range, i+1) - usedClaymore);
        if (curZombie > 0) ++usedClaymore;
        if (usedClaymore > claymore) {
            cout << "NO";
            return 0;
        }
    }
    
    cout << "YES";
    
    return 0;
}
