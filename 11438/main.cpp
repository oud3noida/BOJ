#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 100000;
int n, query, count, idx_t;
vector<int> adj[MAX], child[MAX];
queue<int> nextParent;
int queryIdx[MAX+1],    // Renumbered vertex (in order to check the depth of a vertex)
    traversal[2*MAX],   // Result of inorder traversal
    firstVisit[MAX],    // First occurence of elements in traversal[]
    minSegTree[8*MAX];  // RMQ Tree of traversal[]
bool visited[MAX];

void traverse(int cur) {
    firstVisit[cur] = idx_t;
    traversal[idx_t++] = cur;
    visited[cur] = true;
    for (int &next : child[cur]) {
        if (visited[next]) continue;
        traverse(next);
        traversal[idx_t++] = cur;
    }
}

int makeSegTree(int idx, int left, int right) {
    int mid = (left + right) / 2;
    
    if (left == right) return minSegTree[idx] = traversal[left];
    
    int leftChild  = makeSegTree(2*idx+1, left, mid),
        rightChild = makeSegTree(2*idx+2, mid+1, right);
    
    if (queryIdx[leftChild] < queryIdx[rightChild])
        minSegTree[idx] = leftChild;
    else
        minSegTree[idx] = rightChild;
    
    return minSegTree[idx];
}

int findLCA(int a, int b, int idx, int left, int right) {
    int mid = (left + right) / 2;
    
    // Query out of range
    if (right < firstVisit[a] || firstVisit[b] < left) return MAX;
    // Current range is a subrange of the query range
    if (firstVisit[a] <= left && right <= firstVisit[b]) return minSegTree[idx];
    
    int leftChild  = findLCA(a, b, 2*idx+1, left, mid),
        rightChild = findLCA(a, b, 2*idx+2, mid+1, right);
    
    if (queryIdx[leftChild] < queryIdx[rightChild])
        return leftChild;
    else
        return rightChild;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    
    int a, b;
    for (int i=0; i<n-1; ++i) {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    
    // Make tree & renumber the vertices
    count = 0;
    nextParent.push(0);
    while (!nextParent.empty()) {
        int cur = nextParent.front(); nextParent.pop();
        visited[cur] = true;
        queryIdx[cur] = count++;
        for (int &next : adj[cur]) {
            if (visited[next]) continue;
            child[cur].push_back(next);
            nextParent.push(next);
        }
    }
    queryIdx[MAX] = MAX;
    
    // Inorder traversal
    for (int i=0; i<n; ++i) visited[i] = false;
    idx_t = 0;
    traverse(0);
    
    // Make a segment tree of traversal[]
    makeSegTree(0, 0, idx_t);
    
    // Query
    cin >> query;
    for (int q=0; q<query; ++q) {
        cin >> a >> b;
        if (firstVisit[a-1] > firstVisit[b-1]) swap(a, b);
        cout << findLCA(a-1, b-1, 0, 0, idx_t) + 1 << "\n";
    }
    
    return 0;
}
