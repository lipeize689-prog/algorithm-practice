#include <bits/stdc++.h>
using namespace std;

void solve(){
    vector<int> a (10);
    for(int i = 0;i < 10;i++){
        cin >> a[i];
    }
    int l, count = 0;cin >> l;
    for(int i : a){
        if(i <= l + 30) count++;
    }
    cout << count << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}