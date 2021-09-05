#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Room {
    int type, attack, hp;
    
    Room(int type, int attack, int hp) :
        type(type), attack(attack), hp(hp) {}
};

int num_rooms;
long long attack_hero;
vector<Room> rooms;

bool is_defeatable(long long max_hp_hero) {
    long long cur_attack_hero = attack_hero;
    long long cur_hp_hero = max_hp_hero;
    
    for (int i = 0; i < num_rooms; i++) {
        auto cur_room = rooms[i];
        if (cur_room.type == 1) {
            int attack_monster = cur_room.attack;
            int hp_monster = cur_room.hp;
            
            cur_hp_hero -= (hp_monster - 1) / cur_attack_hero * attack_monster;
            if (cur_hp_hero <= 0) return false;
        } else {
            cur_attack_hero += cur_room.attack;
            cur_hp_hero = min(max_hp_hero, cur_hp_hero + cur_room.hp);
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_rooms >> attack_hero;
    
    int t, a, h;
    for (int i = 0; i < num_rooms; i++) {
        cin >> t >> a >> h;
        rooms.emplace_back(t, a, h);
    }
    
    long long left = 1;
    long long right = numeric_limits<long long>::max();
    long long ans;
    while (left < right) {
        long long mid = (left + right) / 2;
        if (is_defeatable(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    cout << left;
    
    return 0;
}
