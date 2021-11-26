#include <iostream>
#include <vector>
#include <set>

using namespace std;

constexpr int U = 0, D = 1,
              F = 2, B = 3,
              L = 4, R = 5;
constexpr int FACE[6][4] = {
    {B, R, F, L},
    {F, R, B, L},
    {U, R, D, L},
    {U, L, D, R},
    {U, F, D, B},
    {U, B, D, F},
};
constexpr int BLOCK[6][8][3] = {
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 2, 0},
        {0, 2, 1},
        {0, 2, 2},
        {0, 1, 2},
        {0, 0, 2},
        {0, 0, 1}
    },
    {
        {2, 0, 0},
        {2, 0, 1},
        {2, 0, 2},
        {2, 1, 2},
        {2, 2, 2},
        {2, 2, 1},
        {2, 2, 0},
        {2, 1, 0},
    },
    {
        {0, 0, 0},
        {0, 0, 1},
        {0, 0, 2},
        {1, 0, 2},
        {2, 0, 2},
        {2, 0, 1},
        {2, 0, 0},
        {1, 0, 0},
    },
    {
        {0, 2, 0},
        {1, 2, 0},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2},
        {1, 2, 2},
        {0, 2, 2},
        {0, 2, 1},
    },
    {
        {0, 0, 0},
        {1, 0, 0},
        {2, 0, 0},
        {2, 1, 0},
        {2, 2, 0},
        {1, 2, 0},
        {0, 2, 0},
        {0, 1, 0},
    },
    {
        {0, 0, 2},
        {0, 1, 2},
        {0, 2, 2},
        {1, 2, 2},
        {2, 2, 2},
        {2, 1, 2},
        {2, 0, 2},
        {1, 0, 2},
    }
};

struct Block {
    char color[6];
    
    void rotate_cw(int dir) {
        auto &face = FACE[dir];
        
        for (int i = 1; i <= 3; i++) {
            swap(color[face[0]], color[face[i]]);
        }
    }
    
    void rotate_ccw(int dir) {
        auto &face = FACE[dir];
        
        for (int i = 2; i >= 0; i--) {
            swap(color[face[3]], color[face[i]]);
        }
    }
};

Block cube[3][3][3];

void rotate_cw(int dir) {
    auto &block = BLOCK[dir];
    
    for (int i = 0; i < 8; i++) {
        cube[block[i][0]][block[i][1]][block[i][2]].rotate_cw(dir);
    }
    
    auto &pivot_even = cube[block[0][0]][block[0][1]][block[0][2]];
    auto &pivot_odd = cube[block[1][0]][block[1][1]][block[1][2]];

    for (int i = 2; i <= 7; i++) {
        auto &target = cube[block[i][0]][block[i][1]][block[i][2]];
        
        if (i % 2 == 0) swap(pivot_even, target);
        else swap(pivot_odd, target);
    }
}

void rotate_ccw(int dir) {
    auto &block = BLOCK[dir];
    
    for (int i = 0; i < 8; i++) {
        cube[block[i][0]][block[i][1]][block[i][2]].rotate_ccw(dir);
    }
    
    auto &pivot_odd = cube[block[7][0]][block[7][1]][block[7][2]];
    auto &pivot_even = cube[block[6][0]][block[6][1]][block[6][2]];
    
    for (int i = 5; i >= 0; i--) {
        auto &target = cube[block[i][0]][block[i][1]][block[i][2]];
        
        if (i % 2 == 0) swap(pivot_even, target);
        else swap(pivot_odd, target);
    }
}

int char_to_num(char c) {
    switch (c) {
        case 'U': return U;
        case 'D': return D;
        case 'F': return F;
        case 'B': return B;
        case 'L': return L;
        case 'R': return R;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int num_tests, n;
    string command;
    
    cin >> num_tests;
    for (int t = 0; t < num_tests; t++) {
        for (int up = 0; up < 3; up++) {
            for (int front = 0; front < 3; front++) {
                for (int left = 0; left < 3; left++) {
                    auto &cur = cube[up][front][left];
                    cur = Block();
                    
                    if (up == 0) cur.color[U] = 'w';
                    if (up == 2) cur.color[D] = 'y';
                    if (front == 0) cur.color[F] = 'r';
                    if (front == 2) cur.color[B] = 'o';
                    if (left == 0) cur.color[L] = 'g';
                    if (left == 2) cur.color[R] = 'b';
                }
            }
        }
        
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> command;
            
            if (command[1] == '+')
                rotate_cw(char_to_num(command[0]));
            else
                rotate_ccw(char_to_num(command[0]));
        }
        
        for (int front = 2; front >= 0; front--) {
            for (int left = 0; left < 3; left++) {
                cout << cube[0][front][left].color[U];
            }
            cout << '\n';
        }
    }
    
    return 0;
}
