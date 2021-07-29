#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int num_exams;
vector<int> num_examinees;
int proctor_capacity, vice_capacity;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> num_exams;
    
    num_examinees.assign(num_exams, 0);
    for (int i=0; i<num_exams; ++i) {
        cin >> num_examinees[i];
    }
    
    cin >> proctor_capacity >> vice_capacity;
    
    long long num_proctors = 0;
    for (int i=0; i<num_exams; ++i) {
        double num_unsupervised = num_examinees[i] - proctor_capacity;
        num_proctors += 1 + max(0.0, ceil(num_unsupervised / vice_capacity));
    }
    
    cout << num_proctors;
    
    return 0;
}
