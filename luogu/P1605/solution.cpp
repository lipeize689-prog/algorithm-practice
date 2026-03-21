#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int N, M;
int sx, sy, fx, fy;
int ans = 0;

vector<vector<bool>> visited;

void DFS(int sx, int sy, int fx, int fy){
    if(sx == fx && sy == fy){
        ans++;
        return;
    }
    for(int i = 0;i < 4;i++){
        int nx = sx + dx[i];
        int ny = sy + dy[i];
        if(nx >= 1 && nx <= N && ny >= 1 && ny <= M && !visited[nx][ny]){
            visited[nx][ny] = 1;
            DFS(nx, ny, fx, fy);
            visited[nx][ny] = 0;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> N >> M >> T;
    visited.assign(N + 1, vector<bool> (M + 1, 0));
    cin >> sx >> sy >> fx >> fy;
    while(T-- > 0){
        int mx, my;
        cin >> mx >> my;
        visited[mx][my] = 1;
    }
    visited[sx][sy] = 1;
    DFS(sx, sy, fx, fy);
    cout << ans << "\n";
    return 0;
}