#include <iostream>

using namespace std;

int n;
double ans;
double prize[7][7][7];
double expectation[7][7];

void initPrize() {
    for (int a=1; a<=6; ++a) {
        for (int b=1; b<=6; ++b) {
            expectation[a][b] = 0;
            for (int c=1; c<=6; ++c) {
                if (a == b && b == c) prize[a][b][c] = 10000 + a*1000;
                else if (a == b || a == c) prize[a][b][c] = 1000 + a*100;
                else if (b == c) prize[a][b][c] = 1000 + b*100;
                else prize[a][b][c] = max(a, max(b, c))*100;
                
                expectation[a][b] += prize[a][b][c];
            }
            expectation[a][b] /= 6;
        }
    }
}

void updateExp() {
    double newExpectation[7][7];
    
    for (int a=1; a<=6; ++a) {
        for (int b=1; b<=6; ++b) {
            newExpectation[a][b] = 0;
            for (int c=1; c<=6; ++c) {
                prize[a][b][c] = max(prize[a][b][c], expectation[b][c]);
                newExpectation[a][b] += prize[a][b][c];
            }
            newExpectation[a][b] /= 6;
        }
    }
    
    for (int a=1; a<=6; ++a) {
        for (int b=1; b<=6; ++b) {
            expectation[a][b] = newExpectation[a][b];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    initPrize();
    for (int i=0; i<n-3; ++i) updateExp();
    
    for (int a=1; a<=6; ++a) {
        for (int b=1; b<=6; ++b) {
            ans += expectation[a][b];
        }
    }
    ans /= 6*6;
    
    cout.precision(16);
    cout << ans;
    
    return 0;
}
