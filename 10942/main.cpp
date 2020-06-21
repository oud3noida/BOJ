#include <iostream>

using namespace std;

const int MAX = 2000;
int n, m, s, e;
int arr[MAX];
bool isPalindrome[MAX][MAX];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for (int i=0; i<n; i++) cin >> arr[i];
    
    // Case 1: the length is odd
    for (int i=0; i<n; i++) {
        int a=i, b=i;
        bool curPalindrome = true;
        while (0 <= a && b < n) {
            if (arr[a] != arr[b]) curPalindrome = false;
            isPalindrome[a--][b++] = curPalindrome;
        }
    }
    
    // Case 2: the length is even
    for (int i=0; i<n-1; i++) {
        int a=i, b=i+1;
        bool curPalindrome = true;
        while (0 <= a && b < n) {
            if (arr[a] != arr[b]) curPalindrome = false;
            isPalindrome[a--][b++] = curPalindrome;
        }
    }
    
    cin >> m;
    for (int q=0; q<m; q++) {
        cin >> s >> e;
        cout << isPalindrome[s-1][e-1] << "\n";
    }
    
    return 0;
}
