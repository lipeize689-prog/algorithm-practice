// 原题链接: https://www.luogu.com.cn/problem/P1029
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int p, q;
    cin >> p >> q;
    
    if (q % p != 0) {
        cout << "0\n";
        return;
    }
    
    int k = q / p;
    int count = 0;
    int temp = k;
    
    for (int i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            count++;
            while (temp % i == 0) temp /= i;
        }
    }
    if (temp > 1) count++;
    
    cout << (1 << count) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}