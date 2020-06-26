#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007, BLDG = 8, LOGMAX = 30;
int d;
vector<long long> route[LOGMAX][BLDG];
long long ans[BLDG][BLDG], tmpAns[BLDG][BLDG];

void initialize() {
    route[0][0] = {0, 1, 1, 0, 0, 0, 0, 0};     // 정보과학관
    route[0][1] = {1, 0, 1, 1, 0, 0, 0, 0};     // 전산관
    route[0][2] = {1, 1, 0, 1, 1, 0, 0, 0};     // 미래관
    route[0][3] = {0, 1, 1, 0, 1, 1, 0, 0};     // 신양관
    route[0][4] = {0, 0, 1, 1, 0, 1, 0, 1};     // 한경직기념관 
    route[0][5] = {0, 0, 0, 1, 1, 0, 1, 0};     // 진리관
    route[0][6] = {0, 0, 0, 0, 0, 1, 0, 1};     // 학생회관
    route[0][7] = {0, 0, 0, 0, 1, 0, 1, 0};     // 형남공학관
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    // The map is hardcoded
    initialize();
    
    cin >> d;
    // Calculate the number of ways to be in building 'to' at time (2^'t'),
    // if started from building 'from' at time 0.
    for (int t=1; (1<<t)<=d; ++t) {
        for (int i=0; i<BLDG; ++i) {
            for (int j=0; j<BLDG; ++j) {
                route[t][i].push_back(0);
                for (int k=0; k<BLDG; ++k) {
                    route[t][i][j] += (route[t-1][i][k] * route[t-1][j][k]) % MOD;
                }
                route[t][i][j] %= MOD;
            }
        }
    }
    
    bool lsb = true;
    for (int b=0; (1<<b)<=d; ++b) {
        if (!(d & (1<<b))) continue;
        
        if (lsb) {
            for (int i=0; i<BLDG; ++i)
                for (int j=0; j<BLDG; ++j)
                    ans[i][j] = route[b][i][j];
            lsb = false;
            continue;
        }
        
        for (int i=0; i<BLDG; ++i) {
            for (int j=0; j<BLDG; ++j) {
                tmpAns[i][j] = ans[i][j];
            }
        }
        
        for (int i=0; i<BLDG; ++i) {
            for (int j=0; j<BLDG; ++j) {
                ans[i][j] = 0;
                for (int k=0; k<BLDG; ++k) {
                    ans[i][j] += (tmpAns[i][k] * route[b][j][k]) % MOD;
                }
                ans[i][j] %= MOD;
            }
        }
    }
    
    cout << ans[0][0];
    
    return 0;
}
