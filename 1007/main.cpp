#include <iostream>
#include <cmath>

using namespace std;

// Use pair<int, int> as a vector
#define intPair pair<int,int>

const double INF = 98765432101;
int n;
intPair point[20];
double cache[1<<20];

intPair operator+(intPair a, intPair b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

intPair operator-(intPair a, intPair b) {
    return make_pair(a.first - b.first, a.second - b.second);
}

double norm(intPair vec) {
    double x = vec.first, y = vec.second;
    return sqrt(x*x + y*y);
}

double leastVectorSum(int chosen) {
    int countChosen = __builtin_popcount(chosen);
    
    // If half of the points are chosen, calculate the norm of the following vector:
    // (Vector sum of the chosen vectors) - (Vector sum of the rest)
    if (countChosen == n/2) {
        if (cache[chosen] != -1) return cache[chosen];
        // NOTE: The norm of A-B is equal to that of B-A
        if (cache[(1<<n)-1 & ~chosen] != -1) return cache[(1<<n)-1 & ~chosen];
        
        intPair sum = make_pair(0, 0);
        for (int i=0; i<n; ++i) {
            if (chosen & (1<<i)) sum = sum + point[i];
            else sum = sum - point[i];
        }
        
        return cache[chosen] = norm(sum);
    }
    
    // Find the most significant bit that is set
    int i = 0, tmp = chosen;
    while (tmp > 0) {
        tmp >>= 1;
        ++i;
    }
    
    double ret = INF;
    for (; i<n; ++i) {
        // If the number of points we have to choose is greater than
        //    the number of non-chosen points, end the loop
        if (n-i < n/2 - countChosen) break;
        
        ret = min(ret, leastVectorSum(chosen|(1<<i)));
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int T;
    cin >> T;
    cout << fixed;
    
    for (int t=0; t<T; t++) {
        cin >> n;
        
        for (int i=0; i<(1<<n); i++) cache[i] = -1;
        
        int a, b;
        for (int i=0; i<n; i++) {
            cin >> a >> b;
            point[i] = make_pair(a, b);
        }
        
        cout << leastVectorSum(0) << "\n";
    }
}
