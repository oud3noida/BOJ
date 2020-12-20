#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

const char OP[4] = {'+', '-', '*', '/'};
vector<pair<int, char>> priority;
int L;
string rawFormula;
list<long long> nums;
list<char> ops;

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int p;
    for (int i=0; i<4; ++i) {
        cin >> p;
        priority.push_back(make_pair(p, OP[i]));
    }
    sort(priority.begin(), priority.end());
    
    cin >> rawFormula;
    L = rawFormula.length();
    
    nums.push_back(0);
    for (int i=0; i<L; ++i) {
        if ('0' <= rawFormula[i] && rawFormula[i] <= '9')  {
            nums.back() = nums.back() * 10LL + (rawFormula[i] - '0');
        } else {
            nums.push_back(0);
            ops.push_back(rawFormula[i]);
        }
    }
    
    for (int o=3; o>=0; --o) {
        char op = priority[o].second;
        
        auto itO = --ops.end();
        auto itN1 = --nums.end();
        auto itN2 = --nums.end();
        --itN2;
        
        while (itO != --ops.begin()) {
            if (*itO == op) {
                long long newNum = calc(*itN1, *itO, *itN2);
                itO = ops.erase(itO);
                nums.insert(itN1, newNum);
                itN1 = nums.erase(itN1);
                itN2 = nums.erase(itN2);
            }
            
            --itO; --itN1; --itN2;
        }
    }
    
    cout << nums.front();
    
    return 0;
}