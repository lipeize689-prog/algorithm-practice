#include <bits/stdc++.h>
using namespace std;

void solve(){
    int k, n = 1;
    double sum = 0.0;
    cin >> k;
    while(sum <= k){
        sum += 1.0/n;
        n++;
    }
    cout << n - 1<< "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}