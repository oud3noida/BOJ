#include <iostream>
#include <queue>

using namespace std;

int L, range, damage, claymore, usedClaymore, curZombie, numNotShot;
queue<int> positionUsedClaymore;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> range >> damage >> claymore;
    
    usedClaymore = 0;
    numNotShot = 0;
    
    for (int i=0; i<L; ++i) {
        cin >> curZombie;
        
        if (!positionUsedClaymore.empty()){
            int claymoreEffectExpire = positionUsedClaymore.front() + range;
            if (i == claymoreEffectExpire) {
                --numNotShot;
                positionUsedClaymore.pop();
            }
        }
        
        curZombie -= damage * (min(range, i+1) - numNotShot);
        
        if (curZombie > 0) {
            ++usedClaymore;
            ++numNotShot;
            positionUsedClaymore.push(i);
        }
        
        if (usedClaymore > claymore) {
            cout << "NO";
            return 0;
        }
    }
    
    cout << "YES";
    
    return 0;
}
