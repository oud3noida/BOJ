#include <iostream>
#include <vector>

using namespace std;

struct Coordinate {
    long long x, y;
    
    Coordinate(long long x, long long y) : x(x), y(y) {}
};

int num_digits;
string from;
vector<char> to;

char quadrant(char source, Coordinate d) {
    char REF[2][2] = {{'3', '4'}, {'2', '1'}};
    
    long long x = d.x, y = d.y;
    
    switch (source) {
        case '1':
            return REF[((1-y)%2+2)%2][((1+x)%2+2)%2];
        case '2':
            return REF[((1-y)%2+2)%2][((0+x)%2+2)%2];
        case '3':
            return REF[((0-y)%2+2)%2][((0+x)%2+2)%2];
        case '4':
            return REF[((0-y)%2+2)%2][((1+x)%2+2)%2];
    }
    
    return '0';
}

Coordinate carry(char source, Coordinate d) {
    long long x = d.x, y = d.y;
    
    switch (source) {
        case '1':
            if (x >= 0) x = (x+1)/2;
            else x /= 2;
            if (y >= 0) y = (y+1)/2;
            else y /= 2;
            break;
        case '2':
            if (x >= 0) x /= 2;
            else x = (x-1)/2;
            if (y >= 0) y = (y+1)/2;
            else y /= 2;
            break;
        case '3':
            if (x >= 0) x /= 2;
            else x = (x-1)/2;
            if (y >= 0) y /= 2;
            else y = (y-1)/2;
            break;
        case '4':
            if (x >= 0) x = (x+1)/2;
            else x /= 2;
            if (y >= 0) y /= 2;
            else y = (y-1)/2;
            break;
    }
    
    return Coordinate(x, y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_digits >> from;
    
    long long x, y;
    cin >> x >> y;
    Coordinate d(x, y);
    
    for (int i=num_digits-1; i>=0; --i) {
        to.push_back(quadrant(from[i], d));
        d = carry(from[i], d);
    }
    
    if (d.x != 0 || d.y != 0) {
        cout << -1;
        return 0;
    }
    
    for (auto it = to.rbegin(); it != to.rend(); ++it) {
        cout << *it;
    }
    
    return 0;
}
