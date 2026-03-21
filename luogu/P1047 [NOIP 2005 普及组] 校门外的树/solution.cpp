#include <bits/stdc++.h>
using namespace std;

void solve(){
    int l, m;
    cin >> l;cin >> m;
    vector<int> s (l + 1, 0);
    for(int i = 0;i < m;i++){
        int x, y;
        cin >> x;cin >> y;
        for(int j = x;j <= y;j++){
            s[j]++;
        }
    }
    int count = 0;
    for(int a : s){
        if(!a) count++;
    }
    cout << count << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}