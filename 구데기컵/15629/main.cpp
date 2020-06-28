#include <iostream>
#include <vector>

using namespace std;

const int south_africa__namibia = 40,
               zambia__zimbabwe = 0,
               zimbabwe__zambia = 20;
int n, ans;
vector<string> key = {"botswana", "ethiopia", "kenya", "namibia",
                      "south-africa", "tanzania", "zambia", "zimbabwe"};
vector<int> value = {0, 50, 50, 140, 0, 50, 50, 30};
bool visited__south_africa;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    visited__south_africa = false;
    
    string prev = "", cur;
    for (int i=0; i<n; ++i) {
        cin >> cur;
        for (int j=0; j<8; ++j) {
            if (cur != key[j]) continue;
            
            if (prev == key[6] && j == 7) {
                ans += zambia__zimbabwe;
            } else if (prev == key[7] && j == 6) {
                ans += zimbabwe__zambia;
            } else if (visited__south_africa && j == 3) {
                ans += south_africa__namibia;
            } else {
                ans += value[j];
            }
            
            if (j == 4) visited__south_africa = true;
            
            break;
        }
        prev = cur;
    }
    
    cout << ans;
    
    return 0;
}
