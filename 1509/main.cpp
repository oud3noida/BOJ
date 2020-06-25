#include <iostream>
#include <vector>

using namespace std;

const int MAX = 2500;
string S;
int n, ans;
int cache[MAX];
// Possible lengths of a palindrome starting at S[i]
vector<int> pLength[MAX];

int minPartition(int i) {
    if (i == n) return 0;
    
    int &ret = cache[i];
    if (ret != -1) return ret;
    
    ret = MAX;
    for (auto l=pLength[i].begin(); l!=pLength[i].end(); ++l) {
        ret = min(ret, 1 + minPartition(i + *l));
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> S;
    n = S.length();
    ans = 0;
    
    for (int i=0; i<n; i++) {
        pLength[i].push_back(1);
        cache[i] = -1;
    }
    
    // Case 1: the length is odd
    for (int i=0; i<n; i++) {
        int d = 1;
        while (0 <= i-d && i+d < n) {
            if (S[i-d] != S[i+d]) break;
            pLength[i-d].push_back(2*d+1);
            ++d;
        }
    }
    
    // Case 2: the length is even
    for (int i=0; i<n-1; i++) {
        int d = 0, j = i+1;
        while (0 <= i-d && j+d < n) {
            if (S[i-d] != S[j+d]) break;
            pLength[i-d].push_back(2*d+2);
            ++d;
        }
    }
    
    cout << minPartition(0);
    
    return 0;
}
