#include <iostream>
#include <cmath>

using namespace std;

constexpr int LOG_2_MAX = 30,
              LOG_5_MAX = 13;
int n, m;

int number_of_factor(int n, int factor, int LOG_MAX) {
    int ret = 0;
    for (int i=1; i<=LOG_MAX; ++i) {
        ret += n/pow(factor, i);
    }
    return ret;
}

int number_of_2(int n) {
    return number_of_factor(n, 2, LOG_2_MAX);
}

int number_of_5(int n) {
    return number_of_factor(n, 5, LOG_5_MAX);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    int sum_number_of_5 = number_of_5(n) - number_of_5(m) - number_of_5(n-m),
        sum_number_of_2 = number_of_2(n) - number_of_2(m) - number_of_2(n-m);
    
    cout << min(sum_number_of_2, sum_number_of_5);
    
    return 0;
}
