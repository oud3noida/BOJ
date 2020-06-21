// Shoelace formula(a.k.a. Gauss's area formula):
//      https://en.wikipedia.org/wiki/Shoelace_formula

#include <iostream>
#include <cmath>

using namespace std;

int n;
long long area;

long long crossProduct(pair<int, int> a, pair<int, int> b) {
    long long x0 = a.first, y0 = a.second, x1 = b.first, y1 = b.second;
    return x0*y1 - x1*y0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    area = 0.0;
    
    int x, y;
    pair<int, int> v0, vi, vj;
    
    cin >> x >> y;
    vi = v0 = make_pair(x, y);
    for (int i=0; i<n-1; i++) {
        cin >> x >> y;
        vj = make_pair(x, y);
        area += crossProduct(vi, vj);
        vi = vj;
    }
    area += crossProduct(vj, v0);
    
    cout << (abs(area) / 2) << ((abs(area) % 2 == 0) ? ".0" : ".5");
    
    return 0;
}
