#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
int d;
int route[100001][8];
vector<int> adj[8];

void initialize() {
    adj[0] = {1, 2};            // 정보과학관
    adj[1] = {0, 2, 3};         // 전산관
    adj[2] = {0, 1, 3, 4};      // 미래관
    adj[3] = {1, 2, 4, 5};      // 신양관
    adj[4] = {2, 3, 5, 7};      // 한경직기념관 
    adj[5] = {3, 4, 6};         // 진리관
    adj[6] = {5, 7};            // 학생회관
    adj[7] = {4, 6};            // 형남공학관
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    // The map is hardcoded
    initialize();
    
    route[0][0] = 1;
    for (int bldg=1; bldg<8; bldg++) route[0][bldg] = 0;
    
    cin >> d;
    // Calculate the number of ways to be at building 'bldg' in time 't'
    for (int t=1; t<=d; t++) {
        for (int bldg=0; bldg<8; bldg++) {
            route[t][bldg] = 0;
            for (int next=0; next<adj[bldg].size(); next++) {
                int nextBldg = adj[bldg][next];
                route[t][bldg] += route[t-1][nextBldg];
                route[t][bldg] %= MOD;
            }
        }
    }
    
    cout << route[d][0];
    
    return 0;
}
