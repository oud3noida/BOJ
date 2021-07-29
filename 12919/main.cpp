#include <iostream>

using namespace std;

string initial, final;

bool inversed_traverse(int begin, int end, bool reversed) {
    int &begin_index = reversed ? end : begin,
        &end_index = reversed ? begin : end,
        increment = reversed ? -1 : 1;
    
    if (end - begin + 1 == initial.length()) {
        for (int i=0; i<initial.length(); ++i) {
            if (initial[i] != final[begin_index]) return false;
            begin_index += increment;
        }
        return true;
    }
    
    if (final[end_index] == 'A') {
        end_index -= increment;
        if (inversed_traverse(begin, end, reversed)) return true;
        end_index += increment;
    }
    
    if (final[begin_index] == 'B') {
        begin_index += increment;
        return inversed_traverse(begin, end, !reversed);
    }
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> initial >> final;
    
    if (inversed_traverse(0, final.length() - 1, false)) cout << 1;
    else cout << 0;
    
    return 0;
}
