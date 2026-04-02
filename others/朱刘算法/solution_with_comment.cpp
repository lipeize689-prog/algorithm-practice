#include <bits/stdc++.h>  // 万能头文件，包含所有标准库
using namespace std;       // 使用标准命名空间
typedef long long ll;      // 定义 long long 的简写为 ll

// 定义有向边结构体
struct directedE {
    int from, to;          // 边的起点和终点
    ll weight;             // 边的权重（代价）
    directedE* originalEdge;  // 指向原始边的指针，用于缩点后还原真实边
    
    // 构造函数，originalEdge默认为nullptr
    directedE(int from, int to, ll weight, directedE* originalEdge = nullptr) 
        : from(from), to(to), weight(weight), originalEdge(originalEdge) {}
};

/**
 * 朱刘算法（Chu-Liu/Edmonds Algorithm）实现
 * 功能：找到以 root 为根的最小树形图（有向最小生成树）
 * 
 * @param nodeCount 当前图中的节点数量
 * @param root 根节点编号
 * @param graphEdges 当前图中的所有有向边
 * @return 选中的边集合，如果不存在则返回空vector
 */
vector<directedE*> chuliu(int nodeCount, int root, vector<directedE*>& graphEdges) {
    // ========== 第1步：为每个节点选择最小入边 ==========
    // minIncoming[i] 存储指向节点 i 的权值最小的边
    vector<directedE*> minIncoming(nodeCount, nullptr);
    
    // 遍历所有边，为每个节点找到最小的入边
    for (directedE* edge : graphEdges) {
        // 忽略自环边，忽略指向根节点的边（根节点没有入边）
        if (edge->from == edge->to || edge->to == root) continue;
        
        // 如果该节点还没有入边，或者当前边的权值更小，则更新
        if (minIncoming[edge->to] == nullptr || edge->weight < minIncoming[edge->to]->weight) {
            minIncoming[edge->to] = edge;
        }
    }
    
    // 检查是否有节点（除了根）没有入边，如果没有入边则无法形成树形图
    for (int i = 0; i < nodeCount; i++) {
        if (i != root && minIncoming[i] == nullptr) {
            return {};  // 返回空集，表示无解
        }
    }
    
    // ========== 第2步：检测环并缩点 ==========
    // componentId[i] 记录节点 i 所在的缩点后的组件编号
    vector<int> componentId(nodeCount, -1);
    // visited[i] 记录节点 i 在当前DFS中被哪个起始节点访问过
    vector<int> visited(nodeCount, -1);
    // cycleEdges 存储环上的所有边（稍后需要展开）
    vector<directedE*> cycleEdges;
    int componentCount = 0;  // 组件计数
    
    // 遍历每个节点，找出所有的环
    for (int i = 0; i < nodeCount; i++) {
        if (i == root) continue;        // 跳过根节点
        if (componentId[i] != -1) continue;  // 已经分配了组件编号，跳过
        
        int current = i;  // 从当前节点开始沿着最小入边反向追溯
        // 为什么反向？因为每个节点（除root之外）都有确定的一个入边，但是出边却不一定只有一个
        
        // 沿着最小入边的方向回溯，直到遇到根、已分配组件的节点、或回到本次遍历的起点
        while (current != root && componentId[current] == -1 && visited[current] != i) {
            visited[current] = i;  // 标记该节点被起始节点 i 访问过
            current = minIncoming[current]->from;  // 沿着入边反向移动（找前驱）
        }
        // 如果没有环，到这一步current一定是root
        // 如果找到了一个环（回到了之前访问过的节点，且该节点还未分配组件）
        if (current != root && componentId[current] == -1 && visited[current] == i) {
            int start = current;  // 记录环的起始点
            // 遍历整个环，为环上的每个节点分配相同的组件编号
            do {
                componentId[current] = componentCount;  // 分配组件编号
                cycleEdges.push_back(minIncoming[current]);  // 收集环上的边
                current = minIncoming[current]->from;  // 继续回溯
            } while (current != start);
            componentCount++;  // 增加组件计数
        }
    }
    
    // 如果没有发现任何环，说明已经得到了一棵最小树形图
    if (cycleEdges.empty()) {
        vector<directedE*> selected;  // 存储选中的边
        // 收集所有最小入边（除了根节点的）
        for (int i = 0; i < nodeCount; i++) {
            if (i != root && minIncoming[i] != nullptr) {
                selected.push_back(minIncoming[i]);
            }
        }
        return selected;  // 返回选中的边集
    }
    
    // ========== 第3步：为未在环中的节点分配组件编号 ==========
    // 将不在任何环中的节点各自分配一个独立的组件编号
    for (int i = 0; i < nodeCount; i++) {
        if (componentId[i] == -1) {
            componentId[i] = componentCount++;  // 每个节点单独成为一个组件
        }
    }
    
    // ========== 第4步：构建缩点后的新图 ==========
    vector<directedE*> contractedEdges;  // 存储缩点后的边
    
    // 遍历原图中的每条边
    for (directedE* edge : graphEdges) {
        int newFrom = componentId[edge->from];  // 起点所在的新组件编号
        int newTo = componentId[edge->to];      // 终点所在的新组件编号
        
        // 只保留连接不同组件的边（同一组件内的边会被缩掉）
        if (newFrom != newTo) {
            // 关键步骤：调整边的权值
            // 新权值 = 原权值 - minIncoming[edge->to]->weight
            // 减去入边权值是为了保证最终展开环时总权值正确
            ll newWeight = edge->weight - minIncoming[edge->to]->weight;
            
            // 创建新边，并记录原始边的指针，以便后续展开时恢复
            contractedEdges.push_back(new directedE(newFrom, newTo, newWeight, edge));
        }
    }
    
    // ========== 第5步：递归处理缩点后的图 ==========
    // 递归调用朱刘算法，求解缩点后图的最小树形图
    // 最终只有两种可能（递归终点）：一种是返回空集；另一种是跑一遍算法发现已经是最小树形图了，这时候直接返回这个图
    vector<directedE*> subResult = chuliu(componentCount, componentId[root], contractedEdges);
    // 递归函数操作的是新图，返回的应该是新图中的选择结果
    
    // 如果递归返回空集，说明无解
    if (subResult.empty()) return {};
    
    // ========== 第6步：展开环，恢复真实的边 ==========
    vector<directedE*> finalEdges;  // 存储最终的边集
    
    // 遍历递归结果中的每条边
    for (directedE* contractedEdge : subResult) {
        directedE* realEdge = contractedEdge->originalEdge;  // 获取原始边
        finalEdges.push_back(realEdge);  // 添加真实边
        
        // 如果这条真实边的终点在环中，需要从环中移除对应的边
        // 因为在环中，这条新边会替换掉原来指向该点的入边
        // cycleEdges储存的是真实边
        auto iter = find(cycleEdges.begin(), cycleEdges.end(), minIncoming[realEdge->to]);
        /*
        find() 函数会在 [cycleEdges.begin(), cycleEdges.end()) 范围内搜索 minIncoming[realEdge->to]：

        如果找到了：返回指向该元素的迭代器

        如果没找到：返回 cycleEdges.end()（指向末尾的迭代器，表示"没找到"）
        */
        if (iter != cycleEdges.end()) {
            cycleEdges.erase(iter);  // 从环中移除被替换的边
        }
    }
    
    // 将环中剩余的边（没有被替换的）加入最终结果
    finalEdges.insert(finalEdges.end(), cycleEdges.begin(), cycleEdges.end());
    
    return finalEdges;  // 返回最终选中的边集
}

int main() {
    ios::sync_with_stdio(false);  // 关闭C和C++的输入输出同步，加快速度
    cin.tie(nullptr);             // 解除cin和cout的绑定，进一步加速
    
    int t_count, linkCount;  // t_count: 人数, linkCount: 有向边的数量
    cin >> t_count >> linkCount;
    
    vector<directedE*> allEdges;  // 存储所有的边
    
    // 读入所有的原始边
    for (int i = 0; i < linkCount; i++) {
        int from, to;
        ll cost;
        cin >> from >> to >> cost;
        // 注意：这里将权值乘以了 t_count，这是为了给后续的虚拟边留出空间
        // 乘以 t_count 可以保证虚拟边的权值在数值上大于所有原始边的总和
        allEdges.push_back(new directedE(from, to, cost * t_count, nullptr));
    }
    
    // ========== 添加虚拟源点，用于确定经理 ==========
    /*
        让虚拟源点作为朱刘算法的固定根

        算法运行后，虚拟源点必须连接到所有人

        但虚拟源点不能直接连接到所有人（那是星形结构，成本高）

        所以虚拟源点会先连接到某个人，然后由这个人去连接其他人
    */
    int superSource = t_count;  // 虚拟源点的编号（等于人数，即新增一个节点）
    ll LARGE_VALUE = 10000000LL;  // 一个足够大的值
    
    // 从虚拟源点向每个人添加一条边
    for (int i = 0; i < t_count; i++) {
        // 权值设计：LARGE_VALUE * t_count + i
        // 1. LARGE_VALUE * t_count 确保这条边的权值大于所有原始边的总权值
        //    （因为原始边最多有 t_count 条，每条最大约 LARGE_VALUE-1，总和 < LARGE_VALUE * t_count）
        // 2. + i 是为了在多个经理可选时，优先选择编号较小的
        //    因为编号越小，权值越小，朱刘算法会选择更小的权值
        allEdges.push_back(new directedE(superSource, i, LARGE_VALUE * t_count + i, nullptr));
    }
    
    // 调用朱刘算法，以虚拟源点为根，求解最小树形图
    vector<directedE*> selected = chuliu(t_count + 1, superSource, allEdges);
    
    // 如果没有找到有效的树形图，输出 impossible
    if (selected.empty()) {
        cout << "impossible" << endl;
        // 释放所有动态分配的内存
        for (directedE* edge : allEdges) delete edge;
        return 0;
    }
    
    // ========== 解析结果 ==========
    int superEdgeCount = 0;    // 从虚拟源点出发的边的数量
    ll totalRealCost = 0;      // 总的真实代价
    int managerId = -1;        // 经理的编号
    vector<int> messageSource(t_count, -1);  // messageSource[i] 表示谁给 i 发消息
    
    // 遍历选中的边
    for (directedE* edge : selected) {
        if (edge->from == superSource) {  // 如果这条边是从虚拟源点出发的
            superEdgeCount++;             // 统计数量
            managerId = edge->to;         // 这条边指向的人就是经理
            messageSource[edge->to] = edge->to;  // 经理给自己发消息（标记为管理者）
        } else {  // 如果是普通边
            // 恢复真实权值：除以 t_count（之前乘以了 t_count）
            totalRealCost += edge->weight / t_count;
            // 记录谁给谁发消息：终点 to 的消息来源于起点 from
            messageSource[edge->to] = edge->from;
        }
    }
    
    // 如果从虚拟源点出发的边不止一条，说明经理不唯一，不符合要求
    if (superEdgeCount > 1) {
        cout << "impossible" << endl;
    } else {
        // 输出最小总代价和经理编号
        cout << totalRealCost << " " << managerId << endl;
        
        // 按照要求输出每个节点的消息来源
        for (int i = 0; i < t_count; i++) {
            if (messageSource[i] == i) {  // 如果是经理本人
                cout << i << endl;        // 只输出自己的编号
            } else {                      // 如果是普通节点
                cout << i << " " << messageSource[i] << endl;  // 输出 节点 来源
            }
        }
    }
    
    // 释放所有动态分配的内存，防止内存泄漏
    for (directedE* edge : allEdges) delete edge;
    return 0;
}