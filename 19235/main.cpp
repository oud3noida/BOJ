#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int BEDROCK = 6;

struct Block {
    int row, adj;
    Block(int row, int adj) : row(row), adj(adj) {}
    
    bool operator<(const Block &other) const {
        return row > other.row;
    }
};

struct Board {
    int score;
    vector<vector<Block>> columns;
    
    Board() : score(0) {
        columns.assign(4, vector<Block>(1, Block(BEDROCK, 0)));
    }
    
    void fallBlock(int c) {
        for (auto &b : columns[c]) {
            if (b.row == BEDROCK) continue;
            
            /* -- Notice that columns[c] is already sorted in descending order -- */
            auto curBlock = lower_bound(columns[c].begin(), columns[c].end(), b);
            switch (b.adj) {
                // Single block: find the nearest block below and drop onto it
                case 0:
                {
                    auto floorBlock = curBlock-1;
                    b.row = floorBlock->row - 1;
                    break;
                }
                // Coupled blocks: find nearest blocks below the coupled blocks,
                //                  and drop onto the highest one between the nearest blocks
                case 1:
                {
                    auto adjBlock = lower_bound(columns[c+1].begin(), columns[c+1].end(), b);
                    auto floorBlock1 = curBlock-1;
                    auto floorBlock2 = adjBlock-1;
                    b.row = min(floorBlock1->row, floorBlock2->row) - 1;
                    adjBlock->row = b.row;
                    break;
                }
                case -1:
                {
                    auto adjBlock = lower_bound(columns[c-1].begin(), columns[c-1].end(), b);
                    auto floorBlock1 = adjBlock-1;
                    auto floorBlock2 = curBlock-1;
                    b.row = min(floorBlock1->row, floorBlock2->row) - 1;
                    adjBlock->row = b.row;
                    break;
                }
            }
        }
    }
    
    bool updateScore() {
        bool ret = false;
        
        for (auto b = columns[0].begin()+1; b != columns[0].end();) {
            bool fullRow = true;
            for (int c=1; c<4; ++c) {
                /* -- Notice that columns[c] is already sorted in descending order -- */
                if (!binary_search(columns[c].begin(), columns[c].end(), *b)) {
                    fullRow = false;
                    break;
                }
            }
            
            // If there is no block with the same row as 'b' in the current column,
            //  move onto the next row
            if (!fullRow) {
                ++b;
                continue;
            }
            
            // Get score and erase the row
            ++score;
            for (int c=1; c<4; ++c)
                columns[c].erase(lower_bound(columns[c].begin(), columns[c].end(), *b));
            b = columns[0].erase(b);
            
            ret = true;
        }
        
        // Drop blocks 
        for (int c=0; c<4; ++c) fallBlock(c);
        
        // Return true if there was a score update; otherwise return false
        return ret;
    }
    
    void blockShift() {
        int delta = 0;
        for (int c=0; c<4; ++c) {
            if (columns[c].back().row == 0) {
                delta = 2;
                break;
            } else if (columns[c].back().row == 1) {
                delta = 1;
            }
        }
        
        if (delta == 0) return;
        
        for (int c=0; c<4; ++c) {
            for (auto b = columns[c].begin()+1; b != columns[c].end();) {
                b->row += delta;
                /* -- Notice that the element greater than 6 is removed, ensuring columns[c] to be sorted -- */
                if (b->row < 6) ++b;
                else b = columns[c].erase(b);
            }
        }
    }
    
    void pushBlock(int t, int c) {
        // adj = 0: single block
        // adj = 1: block coupled with a block in the next(+1) column
        // adj = -1: block coupled with a block in the previous(-1) column
        switch (t) {
            case 3:
                columns[c].push_back(Block(1, 0));
            case 1:
                columns[c].push_back(Block(0, 0));
                fallBlock(c);
                break;
            case 2:
                columns[c].push_back(Block(0, 1));
                columns[c+1].push_back(Block(0, -1));
                fallBlock(c);
                break;
        }
        
        bool needUpdate = true;
        while (needUpdate)
            needUpdate = updateScore();
        
        blockShift();
    }
};

int N;
Board greenBoard, blueBoard;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    int t, x, y;
    for (int i=0; i<N; ++i) {
        cin >> t >> x >> y;
        greenBoard.pushBlock(t, y);
        t = (t!=1) ? 5-t: t; // 1->1, 2->3, 3->2
        blueBoard.pushBlock(t, x);
    }
    
    cout << greenBoard.score + blueBoard.score << "\n";
    
    int numBlock = 0;
    for (auto &gr : greenBoard.columns) numBlock += gr.size()-1;
    for (auto &bl : blueBoard.columns) numBlock += bl.size()-1;
    cout << numBlock;
    
    return 0;
}
