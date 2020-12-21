#include <iostream>
#include <vector>

using namespace std;

// (28 * 19)^-1 mod 15 = 13 => 28 * 19 * 13 = 6916
// (19 * 15)^-1 mod 28 = 17 => 19 * 15 * 17 = 4845
// (15 * 28)^-1 mod 19 = 10 => 15 * 28 * 10 = 4200

const int E = 15, S = 28, M = 19;
const int C_E = 6916, C_S = 4845, C_M = 4200;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int e, s, m;
    cin >> e >> s >> m;
    /*
    for (int i=1; i<=E*S*M; ++i) {
        if ((i-1)%E == e-1 && (i-1)%S == s-1 && (i-1)%M == m-1) cout << i;
    }
    */

    cout << ((C_E * e + C_S * s) % (E*S*M) + C_M * m - 1) % (E*S*M) + 1;

    return 0;
}