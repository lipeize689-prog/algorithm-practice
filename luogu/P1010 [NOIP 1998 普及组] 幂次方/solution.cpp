#include <bits/stdc++.h>
using namespace std;

string solve(int a){
    if(a == 1) return "2";
    if(a == 0) return "0";
    vector<int> res;
    int i = 0;
    while(a != 0){
        if(a % 2 == 0){
            i++;
            a = a / 2;
            continue;
        }
        a = (a - 1) / 2;
        res.push_back(i);
        i++;
    }
    reverse(res.begin(), res.end());
    string s;
    for(int j = 0;j < res.size() - 1;j++){
        if(res[j] == 1){
            s += "2+";
            continue;
        }
        s = s + "2(" + solve(res[j]) + ")+";
    }
    if(res[res.size() - 1] != 1) s += "2(" + solve(res[res.size() - 1]) + ")";
    else s += "2";
    return s;
}

int main(){
    int n;
    cin >> n;
    string s = solve(n);
    cout << s << "\n";
}