#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int N = 4, EMPTY = -1, SHARK_ID = 0;
const int DX[8] = {0, -1, -1, -1, 0, 1, 1, 1},
          DY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}
bool inRange(pair<int, int> pos) {
    return 0 <= pos.first && pos.first < N && 0 <= pos.second && pos.second < N;
}

pair<int, int> moveFwd(pair<int, int> pos, int dir) {
    return make_pair(pos.first + DX[dir], pos.second + DY[dir]);
}

struct Fish {
    int id, dir;
    pair<int, int> pos;
    
    Fish(int i);
    Fish(Fish* f);
};

Fish::Fish(int i) {
    id = i;
    dir = 0;
    pos = make_pair(-1, -1);
}
Fish::Fish(Fish* f) {
    id = f->id;
    dir = f->dir;
    pos = f->pos;
}

struct FishTank {
    int eatenFish;
    int tank[N][N];
    Fish* fishList[N*N+1];
    
    FishTank();
    FishTank(FishTank* ft);
    
    int& cell(int x, int y);
    int& cell(pair<int, int> pos);
    
    Fish* fish(int id);
    
    vector<pair<int, int>> nextSharkPos();
    
    void updateTank(pair<int, int> nextPos);
};

FishTank::FishTank() {
    eatenFish = 0;
    for (int i=0; i<=N*N; ++i) {
        fishList[i] = new Fish(i);
    }
}
FishTank::FishTank(FishTank* ft) {
    eatenFish = ft->eatenFish;
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            tank[y][x] = ft->tank[y][x];
        }
    }
    for (int i=0; i<=N*N; ++i) {
        if (ft->fishList[i] == NULL) fishList[i] = NULL;
        else fishList[i] = new Fish(ft->fishList[i]);
    }
}

int& FishTank::cell(int x, int y) {
    return tank[y][x];
}
int& FishTank::cell(pair<int, int> pos) {
    return tank[pos.second][pos.first];
}

Fish* FishTank::fish(int id) {
    if (id == EMPTY) return NULL;
    else return fishList[id];
}

vector<pair<int, int>> FishTank::nextSharkPos() {
    assert(fish(SHARK_ID) != NULL);
    
    int sharkDir = fish(SHARK_ID)->dir;
    pair<int, int> sharkPos = fish(SHARK_ID)->pos;
    vector<pair<int, int>> ret;
    
    while (true) {
        sharkPos = moveFwd(sharkPos, sharkDir);
        if (!inRange(sharkPos)) break;
        if (cell(sharkPos) == EMPTY) continue;
        ret.push_back(sharkPos);
    }
    
    return ret;
}

void FishTank::updateTank(pair<int, int> sharkMoveTo) {
    assert(inRange(sharkMoveTo));
    
    // Move shark
    auto shark = fish(SHARK_ID);
    auto preyFish = fish(cell(sharkMoveTo));
    
    if (inRange(shark->pos)) cell(shark->pos) = EMPTY;
    cell(sharkMoveTo) = SHARK_ID;
    
    shark->pos = preyFish->pos;
    shark->dir = preyFish->dir;
    eatenFish += preyFish->id;
    
    fishList[preyFish->id] = NULL;
    
    // Move fish
    for (int i=1; i<=N*N; ++i) {
        auto curFish = fish(i);
        if (curFish == NULL) continue;
        
        int rotate = 0;
        for (; rotate<8; ++rotate) {
            auto moveTo = moveFwd(curFish->pos, curFish->dir);
            if (inRange(moveTo) && cell(moveTo) != SHARK_ID) break;
            curFish->dir = (curFish->dir + 1) % 8;
        }
        if (rotate == 8) continue;
        
        auto moveTo = moveFwd(curFish->pos, curFish->dir);
        auto swapFish = fish(cell(moveTo));
        
        swap(cell(curFish->pos), cell(moveTo));
        if (swapFish != NULL) swap(curFish->pos, swapFish->pos);
        else curFish->pos = moveTo;
    }
}

int maxEatenFish(FishTank *curTank, pair<int, int> sharkMoveTo) {
    curTank->updateTank(sharkMoveTo);
    
    int ret = curTank->eatenFish;
    auto sharkPosCandidates = curTank->nextSharkPos();
    if (sharkPosCandidates.empty()) return ret;
    
    for (auto nextSharkMoveTo : sharkPosCandidates) {
        ret = max(ret, maxEatenFish(new FishTank(curTank), nextSharkMoveTo));
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    FishTank *initTank = new FishTank();
    int i, d;
    for (int y=0; y<N; ++y) {
        for (int x=0; x<N; ++x) {
            cin >> i;
            initTank->cell(x, y) = i;
            initTank->fish(i)->pos = make_pair(x, y);
            
            cin >> d;
            initTank->fish(i)->dir = d-1;
        }
    }
    
    cout << maxEatenFish(initTank, make_pair(0, 0));
    
    return 0;
}
