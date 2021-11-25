#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX = 1000;
vector<int> reg, instructions;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    reg.assign(10, 0);
    instructions.assign(1000, 0);
    
    int x;
    for (int i = 0; cin >> x; ++i) {
        instructions[i] = x;
    }
    
    int i = 0, cnt = 0;
    bool halt = false;
    while (!halt) {
        cnt++;
        int cur = instructions[i++];
        int a = (cur / 10) % 10, b = cur % 10;
        
        switch (cur / 100) {
            case 1:
                halt = true;
                break;
            case 2:
                reg[a] = b;
                break;
            case 3:
                reg[a] = (reg[a] + b) % MAX;
                break;
            case 4:
                reg[a] = (reg[a] * b) % MAX;
                break;
            case 5:
                reg[a] = reg[b];
                break;
            case 6:
                reg[a] = (reg[a] + reg[b]) % MAX;
                break;
            case 7:
                reg[a] = (reg[a] * reg[b]) % MAX;
                break;
            case 8:
                reg[a] = instructions[reg[b]];
                break;
            case 9:
                instructions[reg[b]] = reg[a];
                break;
            case 0:
                if (reg[b] != 0) i = reg[a];
                break;
        }
    }
    
    cout << cnt;
    
    return 0;
}
