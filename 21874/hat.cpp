#include "hat.h"
#include <vector>
using namespace std;

int num_hats;

void init(int N)
{
	num_hats = N;
}

int call(vector<int> F, vector<int> B, int num)
{
    int from_front = F[0];
    for (int i=1; i<num; ++i) {
        from_front = from_front ^ F[i];
    }
    
    int from_back = B[1];
    for (int i=2; i<num_hats; ++i) {
        from_back = from_back ^ B[i];
    }
    
	if (num == num_hats - 1) return from_front;
    if (num == 0) return from_back;
    
    return from_front ^ from_back;
}
