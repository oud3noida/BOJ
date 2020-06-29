#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

const int FLOOR = 2;

struct Cell {
    map<string, Cell*> next;
    int depth;
    
    Cell(int d) : depth(d) {}
    
    Cell* nextCell(string food) {
        auto findFood = next.find(food);
        if (findFood != next.end()) return findFood->second;
        
        Cell *ret = new Cell(depth+FLOOR);
        next.insert(make_pair(food, ret));
        return ret;
    }
    
    bool end() {
        return next.empty();
    }
    
    void printAll() {
        for (auto &child : next) {
            for (int i=0; i<depth; ++i) {
                cout << "-";
            }
            cout << child.first << "\n";
            child.second->printAll();
        }
    }
};

Cell *root;
int n, k;
string food;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    root = new Cell(0);
    
    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> k;
        
        Cell *cur = root;
        for (int j=0; j<k; ++j) {
            cin >> food;
            cur = cur->nextCell(food);
        }
    }
    
    root->printAll();
    
    return 0;
}
