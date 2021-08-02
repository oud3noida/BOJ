#include <iostream>
#include <cmath>

using namespace std;

constexpr double EPSILON = 0.0001;
double x, y, c;

double check(double d) {
    double expect = 1.0 / sqrt(x*x - d*d) + 1.0 / sqrt(y*y - d*d);
    double real = 1.0 / c;
    return expect / real;
}

double find_answer() {
    double d_left = 0, d_right = min(x, y) - EPSILON;
    double d_mid = (d_left + d_right) / 2.0;
    
    while (d_right - d_left > EPSILON) {
        double result = check(d_mid);
        
        cout << d_mid << ' ' << result << endl;
        
        if (result > 1) {
            d_right = d_mid;
        } else {
            d_left = d_mid;
        }
        
        d_mid = (d_left + d_right) / 2.0;
    }
    
    return d_mid;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> x >> y >> c;
    
    cout << fixed;
    cout.precision(20);
    cout << find_answer();
    
    return 0;
}
