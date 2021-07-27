#include <iostream>

using namespace std;

int num_games, num_blocks, height;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_games >> num_blocks >> height;
    
    int y, s;
    string tmp;
    for (int g=0; g<num_games; ++g) {
        cin >> y >> tmp;
        cin >> s >> tmp;
        
        if (num_blocks == 1 || y == s) cout << "YS\n";
        else if (y < s) cout << "Y\n";
        else cout << "S\n";
    }
    
    return 0;
}
