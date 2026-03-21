/*
 *难点在于需要自己实现高精度计算
 *原题链接: https://www.luogu.com.cn/problem/P1009
*/
#include <bits/stdc++.h>
using namespace std;typedef long long ll;

vector<int> sum(vector<int> a, vector<int> b){
    vector<int> c;
    int carry = 0;
    for(int i = 0;i < a.size()||i < b.size()||carry;i++){
        int s = carry;
        if(i < a.size()) s += a[i];
        if(i < b.size()) s += b[i];
        carry = s / 10;
        c.push_back(s % 10);
    }
    return c;
}

vector<int> mul(vector<int> a, int b){
    vector<int> c;
    int carry = 0;
    for(int i = 0;i < a.size()|| carry;i++){
        int m = carry;
        if(i < a.size()) m += a[i] * b;
        carry = m / 10;
        c.push_back(m % 10);
    }
    return c;
}

void solve(){
    int n;
    cin >> n;
    vector<int> a;
    vector<int> s;
    a.push_back(1);
    s.push_back(1);
    for(int i = 2;i <= n;i++){
        a = mul(a, i);
        s = sum(a, s);
    }
    for(int i = s.size() - 1;i >= 0;i--){
        cout << s[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}