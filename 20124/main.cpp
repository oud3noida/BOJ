#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, string>> participants;

bool compScore(pair<int, string> a, pair<int, string> b) {
    return a.first < b.first;
}

bool compName(pair<int, string> a, pair<int, string> b) {
    return a.second > b.second;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    
    string pName;
    int pScore;
    for (int i=0; i<N; ++i) {
        cin >> pName >> pScore;
        participants.push_back(make_pair(pScore, pName));
    }
    
    sort(participants.begin(), participants.end(), compName);
    sort(participants.begin(), participants.end(), compScore);
    
    cout << participants.back().second;
    
    return 0;
}