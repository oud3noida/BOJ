#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000;

enum Membership { O, X, NONE, VISITED };
Membership inTeam[INF + 1];

int n, ans;
int choose[INF + 1];
vector<int> parent[INF + 1];

void visitParent(int cur) {
    /*
        Determines the membership of every student 'par' who chose student 'cur'.
        If student 'par' is already a member of a team(O), does nothing.
        Otherwise(X / NONE / VISITED),
                   student 'par' is determined not to be a member of any team(X),
                   and all the students who chose student 'par' are, too.
                   (unless they are already members of some teams(O))
    */
    for (int i=0; i<parent[cur].size(); i++) {
        int par = parent[cur][i];
        if (inTeam[par] == O) continue;
        inTeam[par] = X;
        visitParent(par);
    }
}

int findCycle(int par, int cur) {
    // If 'cur' is visited, i.e. a cycle is found,
    //     prune all the branches except the ones inside the cycle
    // For more info, refer to the comments of visitParent()
    if (inTeam[cur] == VISITED) {
        inTeam[par] = O;
        visitParent(cur);
        return cur;
    }
    
    inTeam[cur] = VISITED;
    int child = choose[cur] - 1;
    
    int cycleStart = findCycle(cur, child);
    if (cycleStart == cur) return -1;
    else if (inTeam[cur] == O) {
        // Prune all the branches except the ones inside the cycle
        // For more info, refer to the comments of visitParent()
        inTeam[par] = O;
        visitParent(cur);
        return cycleStart;
    }
    return cycleStart;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int c;
    cin >> c;
    for (int t=0; t<c; t++) {
        cin >> n;
        for (int i=0; i<n; i++) parent[i].clear();
        for (int i=0; i<n; i++) {
            cin >> choose[i];
            parent[choose[i]-1].push_back(i);
            inTeam[i] = NONE;
        }
        
        for (int s=0; s<n; s++) {
            if (inTeam[s] != NONE) continue;
            findCycle(INF, s);
        }
        
        ans = n;
        for (int s=0; s<n; s++)
            if (inTeam[s] == O) --ans;
        
        cout << ans << endl;
    }
    
    return 0;
}
