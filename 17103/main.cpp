#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int MAX = 1'000'000;
int num_queries, n;
vector<bool> is_prime;
vector<int> prime_numbers;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    is_prime.assign(MAX + 1, false);
    
    prime_numbers.push_back(2);
    is_prime[2] = true;
    
    for (int i=3; i<=MAX; i+=2) {
        is_prime[i] = true;
        for (int p : prime_numbers) {
            if (p > sqrt(i)) break;
            if (i % p == 0) {
                is_prime[i] = false;
                break;
            }
        }
        if (is_prime[i]) prime_numbers.push_back(i);
    }
    
    cin >> num_queries;
    
    for (int q=0; q<num_queries; ++q) {
        cin >> n;
        
        int num_goldbach_partitions = 0;
        for (int p : prime_numbers) {
            if (p > n/2) break;
            if (is_prime[n-p]) ++num_goldbach_partitions;
        }
        
        cout << num_goldbach_partitions << '\n';
    }
    
    return 0;
}
