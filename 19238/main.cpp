#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pos {
    int x, y;
    Pos(int x=-1, int y=-1) : x(x), y(y) {}
    
    bool operator==(const Pos& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator<(const Pos& other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
};

const int INF = 999;
const int DX[4] = {0, 0, -1, 1},
          DY[4] = {-1, 1, 0, 0};
int N, numCustomer, fuel;
vector<vector<int>> world;
Pos taxi;
vector<Pos> customers, destinations;

bool inRange(const Pos &p) {
    return 0 < p.x && p.x <= N && 0 < p.y && p.y <= N;
}

int findDistance(const Pos &from, const Pos &to) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<pair<Pos, int>> q;
    q.push(make_pair(from, 0));
    visited[from.y-1][from.x-1] = true;
    
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        Pos curPos = cur.first;
        int curDst = cur.second;
        
        if (curPos == to) return curDst;
        
        for (int i=0; i<4; ++i) {
            Pos adjPos = Pos(curPos.x + DX[i], curPos.y + DY[i]);
            if (!inRange(adjPos)) continue;
            if (visited[adjPos.y-1][adjPos.x-1]) continue;
            if (world[adjPos.y-1][adjPos.x-1] == 1) continue;
            visited[adjPos.y-1][adjPos.x-1] = true;
            q.push(make_pair(adjPos, curDst+1));
        }
    }
    
    return -1;
}

bool comp(int a, int b) {
    return customers[a] < customers[b];
}

int findNearestCustomer(int &retDst) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<pair<Pos, int>> q;
    q.push(make_pair(taxi, 0));
    visited[taxi.y-1][taxi.x-1] = true;
    
    vector<int> ret;
    
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        Pos curPos = cur.first;
        int curDst = cur.second;
        
        if (curDst > retDst) break;
        
        if (world[curPos.y-1][curPos.x-1] > 1) {
            if (retDst == INF) retDst = curDst;
            ret.push_back(world[curPos.y-1][curPos.x-1] - 2);
        }
        
        for (int i=0; i<4; ++i) {
            Pos adjPos = Pos(curPos.x + DX[i], curPos.y + DY[i]);
            if (!inRange(adjPos)) continue;
            if (visited[adjPos.y-1][adjPos.x-1]) continue;
            if (world[adjPos.y-1][adjPos.x-1] == 1) continue;
            visited[adjPos.y-1][adjPos.x-1] = true;
            q.push(make_pair(adjPos, curDst+1));
        }
    }
    
    if (retDst == INF) return -1;
    
    sort(ret.begin(), ret.end(), comp);
    return ret.front();
}

int driveTaxi() {
    for (int count=0; count<numCustomer; ++count) {
        // Find the next customer
        int dst = INF;
        int cur = findNearestCustomer(dst);
        if (cur == -1) return -1;
        
        // Drive the customer to the destination
        int reward = findDistance(customers[cur], destinations[cur]);
        fuel -= dst + reward;
        taxi = destinations[cur];
        if (reward == -1) return -1;
        
        world[customers[cur].y-1][customers[cur].x-1] = 0;
        
        // Check and charge fuel
        if (fuel < 0) return -1;
        fuel += reward*2;
    }
    
    return fuel;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> numCustomer >> fuel;
    
    world.assign(N, vector<int>(N, 0));
    for (int y=0; y<N; ++y)
        for (int x=0; x<N; ++x)
            cin >> world[y][x];
    
    cin >> taxi.y >> taxi.x;
    customers.assign(numCustomer, Pos());
    destinations.assign(numCustomer, Pos());
    for (int i=0; i<numCustomer; ++i) {
        cin >> customers[i].y >> customers[i].x;
        cin >> destinations[i].y >> destinations[i].x;
        world[customers[i].y-1][customers[i].x-1] = i+2;
    }
    
    cout << driveTaxi();
    
    return 0;
}
