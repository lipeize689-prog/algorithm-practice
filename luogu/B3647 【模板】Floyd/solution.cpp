// Floyd算法模版
// 来源: https://www.luogu.com.cn/problem/B3647
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n + 1, vector<int> (n + 1, INF));
    while(m-- > 0){
        int u, v, w;
        cin >> u >> v >> w;
        f[u][v] = min(f[u][v], w);
        f[v][u] = min(f[v][u], w);
    }
    for(int i = 1;i <= n;i++){
        f[i][i] = 0;
    }
    for(int k = 1;k <= n;k++){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}