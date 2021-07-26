#include <iostream>
#include <vector>

using namespace std;

const char ESSENTIALS[5] = {'a', 'c', 'i', 'n', 't'};
const int MAX = 26;
int num_words, num_letters;
int taught_bit;
vector<int> words_bit;

int char2int(char c) {
    return c - 'a';
}

bool is_taught(int i) {
    return (taught_bit & (1<<i)) > 0;
}

void teach(int i) {
    taught_bit |= 1<<i;
}

void unteach(int i) {
    taught_bit &= ~(1<<i);
}

int word2bit(string s) {
    int ret = 0;
    for (char c : s) {
        ret |= 1<<char2int(c);
    }
    return ret;
}

bool is_readable(int word_bit) {
    return (taught_bit & word_bit) == word_bit;
}

int max_readable(int cur, int num_letters_to_teach) {
    int ret = 0;
    
    if (num_letters_to_teach == 0) {
        for (auto word : words_bit) {
            ret += is_readable(word) ? 1 : 0;
        }
        return ret;
    }
    
    for (int i=cur; i<MAX-num_letters_to_teach+1; ++i) {
        if (is_taught(i)) continue;
        teach(i);
        ret = max(ret, max_readable(i+1, num_letters_to_teach-1));
        unteach(i);
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_words >> num_letters;
    
    if (num_letters < 5) {
        cout << 0;
        return 0;
    }
    
    taught_bit = 0;
    for (char c : ESSENTIALS) {
        teach(char2int(c));
        --num_letters;
    }
    
    string s;
    for (int i=0; i<num_words; ++i) {
        cin >> s;
        words_bit.push_back(word2bit(s));
    }
    
    cout << max_readable(0, num_letters);
    
    return 0;
}
