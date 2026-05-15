// Edmonds–Karp算法实现
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

constexpr int N = 205;
constexpr int INF = 0x3f3f3f3f;

struct Edge{
    int to, cap, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<Edge> graph[N];
int parent[N];
int parentEdge[N];

void addEdge(int u, int v, int w){
    int u_v_rev = (int)graph[v].size();
    int v_u_rev = (int)graph[u].size();
    graph[u].push_back(Edge(v, w, u_v_rev));
    graph[v].push_back(Edge(u, 0, v_u_rev));
}

bool bfs(int s, int t){
    queue<int> q;
    memset(parent, -1, sizeof parent);
    memset(parentEdge, -1, sizeof parentEdge);
    q.push(s);parent[s] = s;
    while(!q.empty() && parent[t] == -1){
        int u = q.front();q.pop();
        for(int i = 0;i < graph[u].size();i++){
            Edge & e = graph[u][i];
            if(e.cap > 0 && parent[e.to] == -1){
                parent[e.to] = u;
                parentEdge[e.to] = i;
                q.push(e.to);
            }
        }
    }
    return (parent[t] != -1);
}

ll maxFlow(int s, int t){
    ll flow = 0;
    while(bfs(s, t)){
        int cur = t, u = t;
        ll f = INF;

        while(u != s){
            f = min(f, (ll)graph[parent[u]][parentEdge[u]].cap);
            u = parent[u];
        }

        while(cur != s){
            Edge & e = graph[parent[cur]][parentEdge[cur]];
            e.cap -= f;
            graph[cur][e.rev].cap += f;
            cur = parent[cur]; // 这一行一直没看出来少写，卡了半天，妈的
        }
        flow += f;
    }
    return flow;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;cin >> n >> m >> s >> t;
    while(m-- > 0){
        int u, v, w;cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    cout << maxFlow(s, t) << "\n";
    return 0;
}