// 迭代版的DFS解法
#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m, t;
int sx, sy, fx, fy;
vector<vector<bool>> vis; 
int res = 0;

struct node
{
    int x, y, dir;
};


void dfs(pair<int, int> start, pair<int, int> end, vector<vector<bool>> & vis){
    stack<node> s;
    s.push({start.first, start.second, 0});
    while(!s.empty()){
        node & current = s.top();
        if(current.x == end.first && current.y == end.second){
            vis[current.x][current.y] = false;
            res++;
            s.pop();
            continue;
        }
        if(current.dir < 4){
            int nx = current.x + dx[current.dir];
            int ny = current.y + dy[current.dir];
            current.dir++;
            if(nx > 0 && ny > 0 && nx <= n && ny <= m && !vis[nx][ny]){
                s.push({nx, ny, 0});
                vis[nx][ny] = true;
            }
        }else{
            vis[current.x][current.y] = false;
            s.pop();
        }
    } 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> t;
    vis.assign(n + 1, vector<bool> (m + 1, false));
    cin >> sx >> sy >> fx >> fy;
    vis[sx][sy] = true;
    while(t-- > 0){
        int x, y;
        cin >> x >> y;
        vis[x][y] = true;
    }
    dfs({sx, sy}, {fx, fy}, vis);
    cout << res << "\n";
    return 0;
}