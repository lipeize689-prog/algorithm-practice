// 题源: https://www.luogu.com.cn/problem/P3376
// 以下代码是标准 Dinic 算法的实现, 复杂度为O(mn²), 是常用的最大流算法实现
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

constexpr int INF = 0x3f3f3f3f;
constexpr int N = 205;

struct Edge{
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<Edge> graph[N];
int iter[N];
int level[N];

void addEdge(int u, int v, int w){
    int u_v = (int)graph[v].size();
    int v_u = (int)graph[u].size();
    graph[u].push_back(Edge(v, w, u_v));
    graph[v].push_back(Edge(u, 0, v_u));
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
        while((f = dfs(s, t, INF)) > 0){
            flow += f;
        }
    }
    return flow;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    while(m-- > 0){
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    ll ans = maxFlow(s, t);
    cout << ans << "\n";
    return 0;
}