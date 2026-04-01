// https://www.luogu.com.cn/problem/P4017
// 拓扑排序应用
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const int N = 80112002;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph (n + 1);
    vector<int> in (n + 1, 0);
    while(m-- > 0){
        int a, b;
        cin >> a >> b;
        graph[b].push_back(a);
        in[a]++;
    }
    queue<int> q;
    vector<int> res (n + 1, 0);
    for(int i = 1;i <= n;i++){
        if(in[i] == 0){
            q.push(i);
            res[i] = 1;
        }
    }
    while(!q.empty()){
        int current = q.front();q.pop();
        for(int i : graph[current]){
            res[i] = (res[i] + res[current]) % N;
            if(--in[i] == 0) q.push(i);
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(graph[i].empty()){
            ans = (ans + res[i]) % N;
        }
    }
    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}