#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Building {
    int left, right, height;
    
    Building(int left, int height, int right)
        : left(left), right(right), height(height) {}
    
    bool operator<(const Building& other) const {
        return height > other.height;
    }
};

int num_buildings;
vector<Building> buildings;
map<int, int> points;
map<int, int> zero_points;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_buildings;
    
    int l, h, r;
    for (int i=0; i<num_buildings; ++i) {
        cin >> l >> h >> r;
        buildings.emplace_back(l, h, r);
    }
    sort(buildings.begin(), buildings.end());
    
    for (auto &building : buildings) {
        int left = building.left,
            right = building.right,
            height = building.height;
        
        auto it_right = points.lower_bound(right);
        
        if (it_right == points.begin() || (--it_right)->second == 0) {
            points.emplace(right, 0);
            zero_points.emplace(right, 0);
        }
        
        auto it_left = points.lower_bound(left);
        
        if (it_left->first == left) {
            auto zero_it = zero_points.find(left);
            
            if (zero_it != zero_points.end()) {
                zero_points.erase(zero_it);
                it_left->second = height;
                
                if (it_left != points.begin() && prev(it_left)->second == height) {
                    points.erase(it_left);
                }
            }
        } else if (it_left == points.begin() || prev(it_left)->second < height) {
            if (it_left->second == height) {
                points.erase(it_left);
            }
            
            points.emplace(left, height);
        }
        
        auto zero_it_left = zero_points.lower_bound(left);
        
        if (zero_it_left != zero_points.end()) {
            vector<map<int, int>::iterator> zeros_to_erase;
            
            for (auto zero_it = zero_it_left; zero_it->first < right; ++zero_it) {
                auto zero_it_in_points = points.lower_bound(zero_it->first);
                zero_it_in_points->second = height;
                if (zero_it_in_points != points.begin() &&
                    prev(zero_it_in_points)->second == height) {
                    points.erase(zero_it_in_points);
                }
                zeros_to_erase.emplace_back(zero_it);
            }
            
            for (auto &zero : zeros_to_erase) {
                zero_points.erase(zero);
            }
        }
    }
    
    int prev_height = 0;
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (it->second != prev_height)
            cout << it->first << ' ' << it->second << ' ';
        prev_height = it->second;
    }
    
    return 0;
}
