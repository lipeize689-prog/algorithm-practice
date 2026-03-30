// Dijkstra模板题
// 原题链接: https://www.luogu.com.cn/problem/P3371
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int N = 1e4 + 5;
int n, m, s;
int u, v, w;
ll dis[N];
ll M = pow(2, 31) - 1;
bool vis[N];

void solve(){
    memset(vis, false, sizeof(vis));
    cin >> n >> m >> s;
    vector<vector<pair<int, int>>> graph (n + 1);
    while(m-- > 0){
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    for(int i = 1;i <= n;i++){
        dis[i] = INF;
    }
    dis[s] = 0;
    int current = s;
    int next = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    vis[s] = true;
    while (!q.empty())
    {
        current = q.top().second;
        q.pop();
        vis[current] = true;
        for(auto i : graph[current]){
            next = i.first;
            if(vis[next]) continue;
            if(dis[next] > dis[current] + i.second){
                dis[next] = dis[current] + i.second;
                q.push({dis[next], next});
            }
        }
    }
    for(int i = 1;i <= n;i++){
        cout << ((dis[i] == INF) ? M : dis[i]);
        cout << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}