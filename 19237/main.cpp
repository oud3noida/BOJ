#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int DX[4] = {0, 0, -1, 1},
          DY[4] = {-1, 1, 0, 0};
int N;
struct Position;
class Shark;
struct Scent;
class FishTank;


struct Position {
    int x, y;
    
    Position(int x=-1, int y=-1) : x(x), y(y) {}
    
    bool inRange();
    
    Position adj(int dir);
};

class Shark {
    private:
    vector<vector<int>> priority;
    
    public:
    int id, dir;
    Position pos;
    
    Shark(int id=-1, Position pos={-1, -1}, int dir=-1)
    : id(id), pos(pos), dir(dir) {}
    
    void setDir(int dir) {this->dir = dir;}
    void setPriority(vector<vector<int>> p) {this->priority = p;}
    
    Position willMoveTo(FishTank *world);
    
    void move(FishTank *oldWorld, FishTank *newWorld);
};

struct Scent {
    static int duration;
    int id, life;
    
    Scent(int id=-1) : id(id), life(duration) {}
};

class FishTank {
    private:
    vector<vector<int>> sharkTank;
    vector<vector<Scent*>> scentTank;
    
    public:
    vector<Shark*> sharkList;
    
    FishTank(int numShark = 0)
    : sharkTank(vector<vector<int>>(N, vector<int>(N, 0))),
      scentTank(vector<vector<Scent*>>(N, vector<Scent*>(N, NULL))),
      sharkList(vector<Shark*>(numShark+1, NULL)) {}
    
    FishTank(FishTank* prev)
    : sharkTank(vector<vector<int>>(N, vector<int>(N, 0))),
      scentTank(prev->scentTank),
      sharkList(prev->sharkList) {}
    
    int& sharkInCell(Position pos) {return sharkTank[pos.y][pos.x];}
    
    Scent*& scentInCell(Position pos) {return scentTank[pos.y][pos.x];}
    
    FishTank* update();
    
    bool isSharkAlone();
};


bool Position::inRange() {
    return 0 <= x && x < N && 0 <= y && y < N;
}

Position Position::adj(int dir) {
    return Position(this->x + DX[dir], this->y + DY[dir]);
}


int Scent::duration = 0;


Position Shark::willMoveTo(FishTank *world) {
    vector<Position> adjCells(4, -1);
    for (int i=0; i<4; ++i)
        adjCells[i] = this->pos.adj(i);
    
    for (int i : this->priority[this->dir]) {
        if (adjCells[i].inRange() && world->scentInCell(adjCells[i]) == NULL) {
            this->dir = i;
            return adjCells[i];
        }
    }
    
    for (auto &i : this->priority[this->dir]) {
        if (adjCells[i].inRange() && world->scentInCell(adjCells[i])->id == this->id) {
            this->dir = i;
            return adjCells[i];
        }
    }
    
    assert(false);
    return Position();
}

void Shark::move(FishTank *oldWorld, FishTank *newWorld) {
    Position moveTo = this->willMoveTo(oldWorld);
    
    if (newWorld->sharkInCell(moveTo) == 0) {
        newWorld->sharkInCell(moveTo) = this->id;
        this->pos = moveTo;
    } else newWorld->sharkList[this->id] = NULL;
}


FishTank* FishTank::update() {
    FishTank *world = new FishTank(this);
    
    // Sharks leave thier scent
    for (auto cur : this->sharkList) {
        if (cur == NULL) continue;
        world->scentInCell(cur->pos) = new Scent(cur->id);
    }
    
    // Sharks move
    for (auto cur : this->sharkList) {
        if (cur == NULL) continue;
        cur->move(this, world);
    }
    
    // Scent goes away
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            auto curCell = Position(x, y);
            if (world->scentInCell(curCell) == NULL) continue;
            if (--(world->scentInCell(curCell)->life) == 0)
                world->scentInCell(curCell) = NULL;
        }
    }
    
    return world;
}

bool FishTank::isSharkAlone() {
    for (auto cur : this->sharkList) {
        if (cur == NULL || cur->id == 1) continue;
        return false;
    }
    return true;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int numShark;
    cin >> N >> numShark >> Scent::duration;
    
    int i;
    FishTank *curTank = new FishTank(numShark);
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            auto curCell = Position(x, y);
            
            cin >> i;
            curTank->sharkInCell(curCell) = i;
            if (i > 0) curTank->sharkList[i] = new Shark(i, curCell);
        }
    }
    
    int dir;
    for (int s=1; s<=numShark; ++s) {
        cin >> dir;
        curTank->sharkList[s]->setDir(dir-1);
    }
    
    for (int s=1; s<=numShark; ++s) {
        vector<vector<int>> priorityTable(4, vector<int>(4, -1));
        for (int y=0; y<4; ++y) {
            for (int x=0; x<4; ++x) {
                cin >> dir;
                priorityTable[y][x] = dir-1;
            }
        }
        curTank->sharkList[s]->setPriority(priorityTable);
    }
    
    int t = 1;
    for (; t<=1000; ++t) {
        curTank = curTank->update();
        if (curTank->isSharkAlone()) break;
    }
    if (t > 1000) cout << -1;
    else cout << t;
    
    return 0;
}
