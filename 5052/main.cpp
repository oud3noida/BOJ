#include <iostream>

using namespace std;

const char END = '\0';

int char2num(char c) {
    return c - '0';
}

struct phoneNum {
    phoneNum *next[10];
    bool end;
    
    phoneNum() {
        for (int i=0; i<10; ++i) next[i] = NULL;
        end = false;
    }
    
    phoneNum* nextDigit(char c) {
        if (c == END) {
            end = true;
            return NULL;
        }
        
        if (next[char2num(c)] != NULL) return next[char2num(c)];
        
        phoneNum *ret = new phoneNum();
        next[char2num(c)] = ret;
        return ret;
    }
    
    bool notNew() {
        bool ret = false;
        for (int i=0; i<10; ++i) {
            if (next[i] != NULL) ret = true;
        }
        return ret;
    }
};

int T, n;
bool ans;
string phone;
phoneNum *start;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for (int t=0; t<T; ++t) {
        cin >> n;
        start = new phoneNum();
        ans = true;
        
        for (int p=0; p<n; ++p) {
            cin >> phone;
            if (!ans) continue;
            
            int size = phone.size();
            phoneNum *cur = start;
            for (int i=0; i<size; ++i) {
                cur = cur->nextDigit(phone[i]);
                // Check if the current number already exists
                if (cur->end) ans = false;
            }
            // Check if the current number is a prefix of another number
            if (cur->notNew()) ans = false;
            
            // Mark the end of the number
            cur->nextDigit(END);
        }
        
        if (ans) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}
