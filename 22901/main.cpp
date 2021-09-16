#include <iostream>
#include <vector>

using namespace std;

constexpr int LO = 2100, HI = 2399;
int tests;
vector<int> query_count;

bool query(int x) {
    int ret;
    
    cout << "? " << x << endl;
    ++query_count[x - LO];
    
    cin >> ret;
    return ret == 1;
}

void answer(int x) {
    cout << "! " << x << endl;
}

int get_count(int x) {
    return query_count[x - LO];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> tests;
    
    for (int t = 0; t < tests; t++) {
        query_count.assign(HI - LO + 1, 0);
        
        int left = LO;
        int right = HI;
        
        int prev_left = left;
        bool prev_response = false;
        bool lie_detected = false;
        
        while (left < right && !lie_detected) {
            int mid = (left + right + 1) / 2;
            bool response = query(mid);
            
            if (response) {
                prev_left = left;
                left = mid;
            } else {
                if (!lie_detected && prev_response) {
                    if (!query(left)) {
                        lie_detected = true;
                        continue;
                    }
                }
                
                right = mid - 1;
            }
            
            prev_response = response;
        }
        
        if (!lie_detected) {
            if (get_count(left) < 2 && !query(left)) {
                --left;
            }
            
            answer(left);
            continue;
        }
        
        right = left - 1;
        left = prev_left;
        
        while (left < right) {
            int mid = (left + right + 1) / 2;
            
            if (query(mid)) left = mid;
            else right = mid - 1;
        }
        
        answer(left);
    }
    
    return 0;
}
