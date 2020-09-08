#include <iostream>
#include <vector>

using namespace std;

const int DX[4] = {0, 1, 0, -1},
          DY[4] = {1, 0, -1, 0};
int N, M, K, len, ans;
vector<string> board;
string word;
vector<vector<vector<int>>> cache;

bool inRange(int x, int y) {
    return 0 <= x && x < M && 0 <= y && y < N;
}

int makeWord(int x, int y, int cur) {
    if (cur == len) return 1;
    
    int &ret = cache[y][x][cur];
    if (ret != -1) return ret;
    ret = 0;
    
    for (int d=0; d<4; ++d) {
        for (int i=1; i<=K; ++i) {
            int xNext = x + i*DX[d],
                yNext = y + i*DY[d];
            if (inRange(xNext, yNext) && board[yNext][xNext] == word[cur])
                ret += makeWord(xNext, yNext, cur+1);
        }
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M >> K;
    
    board.assign(N, " ");
    for (int y=0; y<N; ++y) cin >> board[y];
    
    cin >> word;
    len = word.length();
    
    cache.assign(N, vector<vector<int>>(M, vector<int>(len, -1)));
    ans = 0;
    for (int y=0; y<N; ++y) {
        for (int x=0; x<M; ++x) {
            if (board[y][x] == word[0])
                ans += makeWord(x, y, 1);
        }
    }
    
    cout << ans;
    
    return 0;
}
