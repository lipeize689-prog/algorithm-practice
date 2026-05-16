// 最大流算法的实际应用, 这道题是最小割思想
// 模版用的是Dinic算法
// 题目链接: https://www.luogu.com.cn/problem/P1646
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 155;
constexpr int INF = 0x3f3f3f3f;

struct Edge{
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<Edge> graph[40 * N * N];
int iter[40 * N * N]; // 当前弧优化
int level[40 * N * N];

void addEdge(int u, int v, int w){
    int u_v_rev = (int)graph[v].size();
    int v_u_rev = (int)graph[u].size();
    graph[u].push_back(Edge(v, w, u_v_rev));
    graph[v].push_back(Edge(u, 0, v_u_rev));
}

bool bfs(int s, int t){
    queue<int> q;
    memset(level, -1, sizeof level);  
    q.push(s);
    level[s] = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i = 0;i < graph[u].size();i++){
            Edge & e = graph[u][i];
            if(e.cap > 0 && level[e.to] == -1){
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return (level[t] != -1);
}

ll dfs(int u, int t, ll f){
    if(u == t) return f;
    for(int & i = iter[u];i < graph[u].size();i++){
        Edge & e = graph[u][i];
        if(e.cap > 0 && level[u] < level[e.to]){
            ll d = dfs(e.to, t, min(f, (ll)e.cap));
            if(d > 0){
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll maxFlow(int s, int t){
    ll flow = 0;
    while(bfs(s, t)){
        memset(iter, 0, sizeof iter);
        ll f;
        while((f = dfs(s, t, INF)) > 0){flow += f;}
    }
    return flow;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;cin >> n >> m;
    int s = 0, t = n * m + 1, tot = n * m + 1;
    ll ans = 0;
    auto id = [&](int i, int j){
        return m * (i - 1) + j;
    };
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int x;cin >> x;ans += x;
            addEdge(s, id(i, j), x);
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int x;cin >> x;ans += x;
            addEdge(id(i, j), t, x);
        }
    }
    for(int i = 1;i < n;i++){
        for(int j = 1;j <= m;j++){
            int x;cin >> x;ans += x;
            addEdge(s, ++tot, x);
            addEdge(tot, id(i+1,j), INF),addEdge(tot, id(i,j), INF);
        }
    }
    for(int i = 1;i < n;i++){
        for(int j = 1;j <= m;j++){
            int x;cin >> x;ans += x;
            addEdge(++tot, t, x);
            addEdge(id(i+1,j), tot, INF),addEdge(id(i,j), tot, INF);
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j < m;j++){
            int x;cin >> x;ans += x;
            addEdge(s, ++tot, x);
            addEdge(tot, id(i,j + 1), INF),addEdge(tot, id(i,j), INF);
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j < m;j++){
            int x;cin >> x;ans += x;
            addEdge(++tot, t, x);
            addEdge(id(i, j + 1), tot, INF),addEdge(id(i, j), tot, INF);
        }
    }
    cout << ans - maxFlow(s, t) << "\n";
    return 0;
}