#include <iostream>
#include <vector>

using namespace std;

int n, num_data, max_seg;
vector<int> psum, cnt;

long long len(int from, int to) {
    return psum[to] - psum[from];
}

long long solve() {
    if (cnt[0] == 0 && cnt[n-1] == 0) {
        // (0)* - (1)* - (0)*
        int i = 0;
        
        while (i < n && cnt[i] == 0)
            i++;
        int from = i;
        
        while (i < n && cnt[i] == 1)
            i++;
        int to = i - 1;
        
        while (i < n && cnt[i] == 0)
            i++;
        
        if (i == n) return len(from, to);
        else return -1;
    } else if (cnt[0] == cnt[n-1]) {
        // (k) - (?) - (k)
        int i = 1;
        int k = cnt[0];
        long long ret = len(0, n-1) * 2*k;
        
        while (i < n-1 && cnt[i] == 2*k)
            i++;
        
        if (i == n-1) {
            // (k) - (2k)* - (k)
            return ret - max_seg; // smallest among possible answers
        } else if (cnt[i] == 2*k - 1) {
            // (k) - (2k)* - (2k-1)* - (2k)* - (k)
            int from = i-1;
            
            while (i < n-1 && cnt[i] == 2*k - 1)
                i++;
            int to = i;
            
            while (i < n-1 && cnt[i] == 2*k)
                i++;
            
            if (i == n-1) return ret - len(from, to);
            else return -1;
        } else if (cnt[i] == 2*k + 1) {
            // (k) - (2k)* - (2k+1)* - (2k)* - (k)
            int from = i;
            
            while (i < n-1 && cnt[i] == 2*k + 1)
                i++;
            int to = i - 1;
            
            while (i < n-1 && cnt[i] == 2*k)
                i++;
            
            if (i == n-1) return ret + len(from, to);
            else return -1;
        } else {
            return -1;
        }
    } else if (abs(cnt[0] - cnt[n-1]) == 1) {
        // (k) - (2k)* - (2k-1)* - (2k-2)* - (k-1)
        int i, d;
        int k = max(cnt[0], cnt[n-1]);
        long long ret = len(0, n-1) * (2*k - 2);
        
        if (cnt[0] > cnt[n-1]) {
            i = 0;
            d = 1;
        } else {
            i = n-1;
            d = -1;
        }
        
        int from = i;
        i += d;
        
        while (0 < i && i < n-1 && cnt[i] == 2*k)
            i += d;
        int mid = i - d;
        
        while (0 < i && i < n-1 && cnt[i] == 2*k - 1)
            i += d;
        int to = i - d;
        
        while (0 < i && i < n-1 && cnt[i] == 2*k - 2)
            i += d;
        
        if (i == 0 or i == n-1) {
            return ret + 2 * len(min(from, mid), max(from, mid)) + len(min(mid, to), max(mid, to));
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> num_data;
    
    psum.assign(n, 0);
    cnt.assign(n, 0);
    max_seg = 0;
    
    int x;
    for (int i = 0; i < n-1; i++) {
        cin >> x;
        psum[i + 1] = psum[i] + x;
        max_seg = max(max_seg, x);
    }
    
    for (int i = 0; i < num_data; i++) {
        cin >> x;
        cnt[x-1]++;
    }
    
    long long ans = solve();
    if (ans != -1) cout << ans;
    else cout << 'F';
    
    return 0;
}
