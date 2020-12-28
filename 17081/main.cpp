#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

using namespace std;

enum ObjectType {
    tEmpty, tWall, tLoot, tTrap, tMonster, tBoss
};
enum LootType {
    lWeapon, lArmor, lBuff
};
enum BuffType {
    bHR, bRE, bCO, bEX, bDX, bHU, bCU
};

class Object {
public:
    ObjectType type;

    explicit Object(ObjectType type = tEmpty) : type(type) {}

    virtual int damage(int virtual_arg) {/* Only for Monster type*/ return 0; }

    virtual bool get_damage(int virtual_arg) {/* Only for Monster type*/ return false; }
};

class Wall : public Object {
public:
    Wall() : Object(tWall) {}
};

class Loot : public Object {
public:
    LootType type;
    int value;

    Loot(LootType loot_type, int value) :
            Object(tLoot), type(loot_type), value(value) {}
};

class Trap : public Object {
public:
    Trap() : Object(tTrap) {}
};

class Monster : public Object {
public:
    string name;
    int health, max_health, attack, defense, xp;

    Monster(string name, int attack, int defense, int health, int xp, ObjectType type = tMonster) :
            Object(type), name(std::move(name)),
            attack(attack), defense(defense), health(health), max_health(health), xp(xp) {}

    int damage(int op_defense) override {
        return max(1, attack - op_defense);
    }

    bool get_damage(int op_damage) override {
        assert(op_damage > 0);
        health -= op_damage;
        return health <= 0;
    }
};

class Boss : public Monster {
public:
    Boss(const string &name, int attack, int defense, int health, int xp) :
            Monster(name, attack, defense, health, xp, tBoss) {}
};

class Buff {
private:
    int number;

public:
    vector<bool> list;

    Buff() : number(0), list(7, false) {}

    void add(BuffType type) {
        if (number < 4 && !list[type]) {
            list[type] = true;
            ++number;
        }
    }

    void use_reincarnation() {
        if (!list[bRE]) return;
        list[bRE] = false;
        --number;
    }
};

class Player {
private:
    int x_init, y_init;

public:
    int x, y;
    int health, max_health, attack, defense;
    int level, xp;
    int weapon, armor;
    Buff accessory;

    Player(int x, int y)
            : x(x), y(y),
              x_init(x), y_init(y),
              health(20), max_health(20), attack(2), defense(2),
              level(1), xp(0),
              weapon(0), armor(0),
              accessory() {}

    bool is_buffed(BuffType type) {
        return accessory.list[type];
    }

    int damage(int op_defense, bool first = false, bool op_boss = false) {
        if (first && op_boss && is_buffed(bHU)) health = max_health;
        int buff_coefficient = (first && is_buffed(bCO)) ? (is_buffed(bDX) ? 3 : 2) : 1;
        return max(1, (attack + weapon) * buff_coefficient - op_defense);
    }

    bool get_damage(int op_damage, bool first_and_op_boss = false) {
        if (first_and_op_boss && is_buffed(bHU)) return false;
        assert(op_damage > 0);
        health -= op_damage;
        return health <= 0;
    }

    bool step_on_trap() {
        health -= (is_buffed(bDX) ? 1 : 5);
        return health <= 0;
    }

    void victory(int gain_xp) {
        if (is_buffed(bHR)) health = min(health + 3, max_health);
        get_xp(gain_xp);
    }

    int max_xp() const {
        return level * 5;
    }

    void get_xp(int gain_xp) {
        xp += (int) (gain_xp * (is_buffed(bEX) ? 1.2 : 1.0));
        if (xp >= max_xp()) {
            level += 1;
            xp = 0;
            max_health += 5;
            health = max_health;
            attack += 2;
            defense += 2;
        }
    }

    string string_state() const {
        stringstream ret;
        ret << "LV : " << level << "\n"
            << "HP : " << (health > 0 ? health : 0) << "/" << max_health << "\n"
            << "ATT : " << attack << "+" << weapon << "\n"
            << "DEF : " << defense << "+" << armor << "\n"
            << "EXP : " << xp << "/" << max_xp() << "\n";
        return ret.str();
    }

    bool reincarnate() {
        if (health > 0 || !is_buffed(bRE)) return false;

        x = x_init;
        y = y_init;
        health = max_health;
        accessory.use_reincarnation();
        return true;
    }
};

class Cell {
private:
    Object *data;
public:
    bool player_inside;

    explicit Cell(ObjectType cell_type, bool player_inside) :
            data(nullptr), player_inside(player_inside) {
        switch (cell_type) {
            case tEmpty:
                data = nullptr;
                return;
            case tWall:
                data = new Wall();
                return;
            case tLoot:
                data = new Object(tLoot);
                return;
            case tTrap:
                data = new Trap();
                return;
            case tMonster:
                data = new Object(tMonster);
                return;
            case tBoss:
                data = new Object(tBoss);
                return;
        }
    }

    bool empty() const {
        return data == nullptr;
    }

    ObjectType type() const {
        if (empty()) return tEmpty;
        else return data->type;
    }

    void create_monster(const string &name, int attack, int defense, int health, int xp) {
        if (type() == tMonster) data = new Monster(name, attack, defense, health, xp);
        else if (type() == tBoss) data = new Boss(name, attack, defense, health, xp);
        else
            assert(false);
    }

    void create_loot(LootType loot_type, int value) {
        data = new Loot(loot_type, value);
    }

    void erase() {
        data = nullptr;
    }

    Loot *loot() const {
        assert(type() == tLoot);
        return (Loot *) data;
    }

    Monster *monster() const {
        assert(type() == tMonster || type() == tBoss);
        return (Monster *) data;
    }

    int damage(int op_defense) const {
        assert(type() == tMonster || type() == tBoss);
        return data->damage(op_defense);
    }

    bool get_damage(int op_attack) const {
        assert(type() == tMonster || type() == tBoss);
        return data->get_damage(op_attack);
    }

    void reincarnate() const {
        if (!(type() == tMonster || type() == tBoss)) return;
        ((Monster *) data)->health = ((Monster *) data)->max_health;
    }

    char type_char() const {
        if (player_inside) return '@';
        switch (type()) {
            case tEmpty:
                return '.';
            case tWall:
                return '#';
            case tLoot:
                return 'B';
            case tTrap:
                return '^';
            case tMonster:
                return '&';
            case tBoss:
                return 'M';
        }
        assert(false);
        return '?';
    }
};

class World {
private:
    int x_max, y_max;
    enum Direction {
        dUp, dDown, dLeft, dRight
    };
    string commands;
    int turn;

    static Direction decrypt_direction(char direction_char) {
        switch (direction_char) {
            case 'U':
                return dUp;
            case 'D':
                return dDown;
            case 'L':
                return dLeft;
            case 'R':
                return dRight;
            default:
                assert(false);
                return dUp;
        }
    }

    static int dx(Direction direction) {
        switch (direction) {
            case dLeft:
                return -1;
            case dRight:
                return 1;
            default:
                return 0;
        }
    }

    static int dy(Direction direction) {
        switch (direction) {
            case dUp:
                return -1;
            case dDown:
                return 1;
            default:
                return 0;
        }
    }

    bool in_range(int x, int y) const {
        return 0 <= x && x < x_max && 0 <= y && y < y_max;
    }

    void move_player(Direction direction) {
        int x_prev = player->x,
                y_prev = player->y,
                x_next = x_prev + dx(direction),
                y_next = y_prev + dy(direction);
        if (in_range(x_next, y_next) && grid[y_next][x_next]->type() != tWall) {
            grid[y_prev][x_prev]->player_inside = false;
            grid[y_next][x_next]->player_inside = true;
            player->x = x_next;
            player->y = y_next;
        }
    }

    bool battle(Cell *cur_cell) const {
        bool is_monster_boss = cur_cell->type() == tBoss;
        int monster_defense = cur_cell->monster()->defense,
                player_defense = player->defense + player->armor;

        bool first = true;
        while (true) {
            int player_damage = player->damage(monster_defense, first, is_monster_boss);
            if (cur_cell->get_damage(player_damage)) {
                player->victory(cur_cell->monster()->xp);
                return true;
            }
            int monster_damage = cur_cell->damage(player_defense);
            if (player->get_damage(monster_damage, first && is_monster_boss)) {
                return false;
            }
            if (first) first = false;
        }
    }

    bool _next_turn(string &game_over_message, Cell *&cur_cell) {
        if (turn == commands.length()) {
            game_over_message = "Press any key to continue.";
            return false;
        }

        move_player(decrypt_direction(commands[turn++]));

        cur_cell = grid[player->y][player->x];
        switch (cur_cell->type()) {
            case tLoot: {
                int loot_value = cur_cell->loot()->value;
                switch (cur_cell->loot()->type) {
                    case lWeapon:
                        player->weapon = loot_value;
                        break;
                    case lArmor:
                        player->armor = loot_value;
                        break;
                    case lBuff:
                        player->accessory.add((BuffType) loot_value);
                        break;
                }
                cur_cell->erase();
                break;
            }
            case tTrap:
                if (player->step_on_trap()) {
                    cur_cell->player_inside = false;
                    game_over_message = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
                    return false;
                }
                break;
            case tMonster:
                if (!battle(cur_cell)) {
                    cur_cell->player_inside = false;
                    game_over_message = "YOU HAVE BEEN KILLED BY " + cur_cell->monster()->name + "..";
                    return false;
                }
                cur_cell->erase();
                break;
            case tBoss:
                if (!battle(cur_cell)) {
                    cur_cell->player_inside = false;
                    game_over_message = "YOU HAVE BEEN KILLED BY " + cur_cell->monster()->name + "..";
                } else {
                    cur_cell->erase();
                    game_over_message = "YOU WIN!";
                }
                return false;
            default:
                break;
        }
        return true;
    }

public:
    Player *player;
    vector<vector<Cell *>> grid;

    World(int x_max, int y_max) : x_max(x_max), y_max(y_max), turn(0) {
        grid.assign(y_max, vector<Cell *>(x_max, nullptr));
        player = nullptr;
    }

    void input_info() {
        int num_monster = 0, num_loot = 0;

        char cell_char;
        ObjectType cell_type;
        for (int y = 0; y < y_max; ++y) {
            for (int x = 0; x < x_max; ++x) {
                bool player_inside = false;
                cin >> cell_char;
                switch (cell_char) {
                    case '@':
                        assert(player == nullptr);
                        player = new Player(x, y);
                        player_inside = true;
                    case '.':
                        cell_type = tEmpty;
                        break;
                    case '#':
                        cell_type = tWall;
                        break;
                    case 'B':
                        ++num_loot;
                        cell_type = tLoot;
                        break;
                    case '^':
                        cell_type = tTrap;
                        break;
                    case '&':
                        ++num_monster;
                        cell_type = tMonster;
                        break;
                    case 'M':
                        ++num_monster;
                        cell_type = tBoss;
                        break;
                    default:
                        assert(false);
                }
                grid[y][x] = new Cell(cell_type, player_inside);
            }
        }

        cin >> commands;

        int x, y;
        for (int i = 0; i < num_monster; ++i) {
            string name;
            int attack, defense, health, xp;
            cin >> y >> x >> name >> attack >> defense >> health >> xp;
            grid[y - 1][x - 1]->create_monster(name, attack, defense, health, xp);
        }
        for (int i = 0; i < num_loot; ++i) {
            char loot_type;
            cin >> y >> x >> loot_type;
            switch (loot_type) {
                case 'W': {
                    int value;
                    cin >> value;
                    grid[y - 1][x - 1]->create_loot(lWeapon, value);
                    break;
                }
                case 'A': {
                    int value;
                    cin >> value;
                    grid[y - 1][x - 1]->create_loot(lArmor, value);
                    break;
                }
                case 'O': {
                    string accessory_name;
                    cin >> accessory_name;
                    BuffType accessory_type;
                    if (accessory_name == "HR") accessory_type = bHR;
                    else if (accessory_name == "RE") accessory_type = bRE;
                    else if (accessory_name == "CO") accessory_type = bCO;
                    else if (accessory_name == "EX") accessory_type = bEX;
                    else if (accessory_name == "DX") accessory_type = bDX;
                    else if (accessory_name == "HU") accessory_type = bHU;
                    else if (accessory_name == "CU") accessory_type = bCU;
                    else
                        assert(false);
                    grid[y - 1][x - 1]->create_loot(lBuff, accessory_type);
                    break;
                }
                default:
                    assert(false);
            }
        }
    }

    bool next_turn(string &game_over_message) {
        Cell *cur_cell = nullptr;
        bool ret = _next_turn(game_over_message, cur_cell);
        if (!ret && player->reincarnate()) {
            grid[player->y][player->x]->player_inside = true;
            cur_cell->reincarnate();
            return true;
        }
        return ret;
    }

    void print(string &game_over_message) {
        for (int y = 0; y < y_max; ++y) {
            for (int x = 0; x < x_max; ++x) {
                cout << grid[y][x]->type_char();
            }
            cout << "\n";
        }

        cout << "Passed Turns : " << turn << "\n"
             << player->string_state()
             << game_over_message;
    }
};

World *world;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int x_max, y_max;
    cin >> y_max >> x_max;
    world = new World(x_max, y_max);

    world->input_info();

    string game_over_message;
    while (world->next_turn(game_over_message));
    world->print(game_over_message);

    return 0;
}