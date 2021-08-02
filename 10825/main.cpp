#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int korean, english, math;
    
    Student(string name, int k, int e, int m)
        : name(name), korean(k), english(e), math(m) {}
    
    bool operator<(const Student& other) const {
        if (korean != other.korean) return korean > other.korean;
        if (english != other.english) return english < other.english;
        if (math != other.math) return math > other.math;
        return name < other.name;
    }
};

int n;
vector<Student> students;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    string name;
    int k, e, m;
    for (int i=0; i<n; ++i) {
        cin >> name >> k >> e >> m;
        students.emplace_back(name, k, e, m);
    }
    
    sort(students.begin(), students.end());
    
    for (auto &s : students) {
        cout << s.name << '\n';
    }
    
    return 0;
}
