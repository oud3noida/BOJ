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
            if (world[adjPos.y-1][adjPos.x-1]) continue;
            visited[adjPos.y-1][adjPos.x-1] = true;
            q.push(make_pair(adjPos, curDst+1));
        }
    }
    
    return -1;
}

bool comp(int a, int b) {
    return customers[a] < customers[b];
}

int driveTaxi() {
    vector<bool> completed(numCustomer, false);
    
    for (int count=0; count<numCustomer; ++count) {
        // Find the nearest customers
        vector<int> candidates;
        int dst = INF;
        for (int i=0; i<numCustomer; ++i) {
            if (completed[i]) continue;
            
            int curDst = findDistance(taxi, customers[i]);
            
            // If failed to get to the customer, stop driving
            if (curDst == -1) return -1;
            
            if (dst == INF) {
                candidates.push_back(i);
                dst = curDst;
            } else if (curDst == dst) {
                candidates.push_back(i);
            } else if (curDst < dst) {
                candidates.clear();
                candidates.push_back(i);
                dst = curDst;
            }
        }
        
        // Tie-break
        sort(candidates.begin(), candidates.end(), comp);
        int cur = candidates.front();
        
        // Drive the customer to the destination
        int reward = findDistance(customers[cur], destinations[cur]);
        fuel -= dst + reward;
        taxi = destinations[cur];
        
        // Check and charge fuel
        if (fuel < 0) return -1;
        fuel += reward*2;
        
        completed[cur] = true;
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
    }
    
    cout << driveTaxi();
    
    return 0;
}
