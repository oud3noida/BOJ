#include <iostream>

using namespace std;

const int MAX = 100000, INF = 1987654321;
int n, query;
int arr[MAX], minSegTree[4*MAX], maxSegTree[4*MAX];

int makeMinSegTree(int idx, int left, int right) {
    int mid = (left + right) / 2;
    
    if (left == right) return minSegTree[idx] = arr[left];
    
    int leftChild  = makeMinSegTree(2*idx+1, left, mid),
        rightChild = makeMinSegTree(2*idx+2, mid+1, right);
    return minSegTree[idx] = min(leftChild, rightChild);
}

int makeMaxSegTree(int idx, int left, int right) {
    int mid = (left + right) / 2;
    
    if (left == right) return maxSegTree[idx] = arr[left];
    
    int leftChild  = makeMaxSegTree(2*idx+1, left, mid),
        rightChild = makeMaxSegTree(2*idx+2, mid+1, right);
    return maxSegTree[idx] = max(leftChild, rightChild);
}

int findMin(int arrLeft, int arrRight, int idx, int treeLeft, int treeRight) {
    int treeMid = (treeLeft + treeRight) / 2;
    
    // Query out of range
    if (treeRight < arrLeft || arrRight < treeLeft) return INF;
    // Current range is a subrange of the query range
    if (arrLeft <= treeLeft && treeRight <= arrRight) return minSegTree[idx];
    
    int leftChild  = findMin(arrLeft, arrRight, 2*idx+1, treeLeft, treeMid),
        rightChild = findMin(arrLeft, arrRight, 2*idx+2, treeMid+1, treeRight);
    return min(leftChild, rightChild);
}

int findMax(int arrLeft, int arrRight, int idx, int treeLeft, int treeRight) {
    int treeMid = (treeLeft + treeRight) / 2;
    
    // Query out of range
    if (treeRight < arrLeft || arrRight < treeLeft) return 0;
    // Current range is a subrange of the query range
    if (arrLeft <= treeLeft && treeRight <= arrRight) return maxSegTree[idx];
    
    int leftChild  = findMax(arrLeft, arrRight, 2*idx+1, treeLeft, treeMid),
        rightChild = findMax(arrLeft, arrRight, 2*idx+2, treeMid+1, treeRight);
    return max(leftChild, rightChild);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> query;
    for (int i=0; i<n; ++i) cin >> arr[i];
    makeMinSegTree(0, 0, n);
    makeMaxSegTree(0, 0, n);
    
    int a, b;
    for (int q=0; q<query; ++q) {
        cin >> a >> b;
        --a; --b;
        cout << findMin(a, b, 0, 0, n) << " " << findMax(a, b, 0, 0, n) << "\n";
    }
    
    return 0;
}
