/*
原题链接: https://www.luogu.com.cn/problem/P1007
上传的第一个黄题
说实话, 这道题需要建立一个直觉: 因为每个士兵的速度都是一样的, 如果他们相遇, 两个人都会向相反的方向走
这一步可以抽象建模为: 两个人相互"穿过去"对方直接向前走, 这个建模和题目是完全等价的
因此最后的最小值就是——谁离最近的出口最远
最大值就是——全局谁离出口最远
问题就解决了！
*/
#include <bits/stdc++.h>
using namespace std;

void solve(){
    int l, n;
    cin >> l >> n;
    if(n == 0) {
        cout << "0 0\n";
        return;
    }
    int max_ = 0, min_ = 0;
    while(n-- > 0){
        int m;
        cin >> m;
        min_ = max(min_, min(l + 1 - m, m));
        max_ = max({max_, l + 1 - m, m});
    }
    cout << min_ << " " << max_ << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}