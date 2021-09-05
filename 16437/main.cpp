#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> num_animals;
vector<vector<int>> children;

long long traverse(int cur) {
    long long ret = num_animals[cur];
    
    for (int child : children[cur]) {
        ret += traverse(child);
    }
    
    return max(0LL, ret);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    num_animals.assign(n, 0);
    children.assign(n, vector<int>());
    
    char t;
    int a, p;
    for (int i = 1; i < n; i++) {
        cin >> t >> a >> p;
        int unary = (t == 'S') ? 1 : -1;
        num_animals[i] = a * unary;
        children[p - 1].push_back(i);
    }
    
    cout << traverse(0);
    
    return 0;
}
