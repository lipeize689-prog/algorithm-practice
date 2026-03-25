// 这个题目我一共上传了两版, 这一版是我写的, AC了, 但是写法太"野"了(ai的评价, 难绷)
// 所以我又让ai帮忙润色了一遍, 加上了一些注释, 放到solution_2里面了, 原题链接也在里面
#include <bits/stdc++.h>
using namespace std;

char p[9]{'0'};
int index_ = -1;

void solve(const string & in_order,const string & post_order){
    if (in_order.empty() || post_order.empty()) return;
    index_++;
    int len = in_order.length();
    char root = post_order[len - 1];
    int c;
    for(int i = 0;i < len;i++){
        if(in_order[i] == root){
            c = i;
            break;
        }
    }
    p[index_] = root;
    string str_in_1 = in_order.substr(0, c);
    string str_in_2 = in_order.substr(c + 1, len - c);
    string str_post_1 = post_order.substr(0, str_in_1.length());
    string str_post_2 = post_order.substr(str_in_1.length(), str_in_2.length());
    solve(str_in_1, str_post_1);
    solve(str_in_2, str_post_2);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string in_o, post_o;
    cin >> in_o >> post_o;
    solve(in_o, post_o);
    for(auto c : p){
        cout << c;
    }
    cout << "\n";
    return 0;
}