#include <iostream>
#include <algorithm>

using namespace std;

int length, n;
int consonant, vowel;
char arr[15], ans[16];

bool isVowel(char c) {
    return (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');
}

void findPasswords(int curLen, int curIdx) {
    if (curLen == length) {
        if (vowel < 1 || consonant < 2) return;
        cout << ans << "\n";
        return;
    }
    
    if (curIdx == n) return;
    
    for (int i=curIdx; i<n; ++i) {
        bool isCurVowel = isVowel(arr[i]);
        
        if (isCurVowel) ++vowel;
        else ++consonant;
        
        ans[curLen] = arr[i];
        findPasswords(curLen+1, i+1);
        
        if (isCurVowel) --vowel;
        else --consonant;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> length >> n;
    for (int i=0; i<n; ++i) cin >> arr[i];
    sort(arr, arr+n);
    
    findPasswords(0, 0);
    
    return 0;
}
