// 原题链接: https://www.luogu.com.cn/problem/P1028
// 解决这种题最好的方式就是先在纸上写几个, 找找规律, 找到规律之后, 状态转移方程就能很快写出来
#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    int res[n + 1];
    int sum[n + 1];
    res[0] = 0;
    res[1] = 1;
    sum[0] = 0;
    sum[1] = 1;
    for(int i = 2;i <= n;i++){
        res[i] = 1 + sum[i / 2];
        sum[i] = sum[i - 1] + res[i];
    }
    cout << res[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}