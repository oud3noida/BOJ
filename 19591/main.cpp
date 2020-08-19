#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

string s;
vector<long long> nums;
vector<char> ops;
int front, back;

long long calc(long long a, char o, long long b) {
    switch (o) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        default: assert(false);
    }
    return 0;
}

bool isPrior(char c) {
    return c == '*' || c == '/';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    nums.push_back(0);
    cin >> s;
    
    int i = 0;
    if (s[0] == '-') {
        i = 1;
        while ('0' <= s[i] && s[i] <= '9') {
            nums.back() = nums.back() * 10LL - (s[i++] - '0');
        }
    }
    
    int length = s.length();
    for (; i<length; ++i) {
        if ('0' <= s[i] && s[i] <= '9')
            nums.back() = nums.back() * 10LL + (s[i] - '0');
        else {
            nums.push_back(0);
            ops.push_back(s[i]);
        }
    }
    
    front = 0;
    back = ops.size() - 1;
    
    while (front < back+1) {
        if (isPrior(ops[front]) && !isPrior(ops[back])) {
            nums[front+1] = calc(nums[front], ops[front], nums[front+1]);
            ++front;
        } else if (!isPrior(ops[front]) && isPrior(ops[back])) {
            nums[back] = calc(nums[back], ops[back], nums[back+1]);
            --back;
        } else {
            long long calcFront = calc(nums[front], ops[front], nums[front+1]);
            long long calcBack = calc(nums[back], ops[back], nums[back+1]);
            
            if (calcFront >= calcBack) nums[++front] = calcFront;
            else nums[back--] = calcBack;
        }
    }
    
    cout << nums[front];
    
    return 0;
}
