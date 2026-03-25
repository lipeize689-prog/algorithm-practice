// 原题链接: https://www.luogu.com.cn/problem/P1030#submit
#include <bits/stdc++.h>
using namespace std;

string preorder;  // 存储先序遍历结果

/**
 * 根据中序和后序遍历序列构建先序遍历
 * @param inorder   中序遍历序列
 * @param postorder 后序遍历序列
 */
void buildPreorder(const string& inorder, const string& postorder) {
    // 递归边界：空树
    if (inorder.empty()) {
        return;
    }
    
    // 1. 后序遍历的最后一个节点是根节点
    char root = postorder.back();
    
    // 2. 在中序遍历中找到根节点的位置
    int rootPos = inorder.find(root);
    
    // 3. 分割中序遍历序列
    string leftInorder  = inorder.substr(0, rootPos);      // 左子树中序
    string rightInorder = inorder.substr(rootPos + 1);     // 右子树中序
    
    // 4. 分割后序遍历序列（根据左子树的节点数）
    int leftSize = leftInorder.size();
    string leftPostorder  = postorder.substr(0, leftSize);                     // 左子树后序
    string rightPostorder = postorder.substr(leftSize, postorder.size() - 1 - leftSize); // 右子树后序
    
    // 5. 先序遍历：根 → 左子树 → 右子树
    preorder += root;
    buildPreorder(leftInorder, leftPostorder);
    buildPreorder(rightInorder, rightPostorder);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string inorder, postorder;
    cin >> inorder >> postorder;
    
    preorder.clear();
    buildPreorder(inorder, postorder);
    
    cout << preorder << "\n";
    
    return 0;
}