/**
 * 高精度加法模版题
 * 问题描述:
 * 给定两个非负整数 a,b，求它们的和。不用考虑负数。
 * 
 * 输入格式:
 * 输入共两行，每行一个非负整数，分别为 a,b。
 * 
 * 输出格式:
 * 输出一行一个非负整数，表示 a+b 的值。
 * 
 * 数据范围:
 * 0 <= a, b <= 1e500
 * 
 * 主要看高精度加法的实现，以及怎么处理大数据输入
 * 
 * 其实高精度加法，容器的每一位不一定只存一位，可以存很多位，比如10000位，这样会大大减小容器的长度。
 * 此时需要做的改动是：计算carry的时候要改成carry = sum / 10000和c.push_back(sum % 10000)——
 * 相当于用10000位进制计算
 * 另外，这个思路在输出的时候也要注意低位补零的问题
 * */
#include<bits/stdc++.h>
using namespace std;

vector<int> add(vector<int> a, vector<int> b){
    vector<int> c;
    int carry = 0;
    // for循环中判断条件要有carry：为了处理i超过了a和b的长度但是还有进位的情况
    for(int i = 0;i < a.size() || i < b.size() || carry;i++){
        // 这种 if 和 += 共用的写法感觉很常见
        int sum = carry;
        if(i < a.size()) sum += a[i];
        if(i < b.size()) sum += b[i];

        c.push_back(sum % 10);
        carry = sum / 10;
    } 
    return c;
}

void solve(){
    // 输入可以用string来处理
    string str_a, str_b;
    cin >> str_a >> str_b;
    vector<int> a, b;
    for(int i = str_a.length() - 1;i >= 0;i--){
        a.push_back(str_a[i] - '0');
    }
    for(int i = str_b.length() - 1;i >= 0;i--){
        b.push_back(str_b[i] - '0');
    }
    vector<int> res = add(a, b);
    for(int i = res.size() - 1;i >= 0;i--){
        cout << res[i];
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}