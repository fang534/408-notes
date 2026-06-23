#include <iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

typedef int elemtype;

// 二叉树节点
struct treenode {
    elemtype data;
    int weight;
    string code="0";
    treenode* left;
    treenode* right;
    treenode(elemtype d, int w)
    {
        data = d;
        weight = w;
        left = nullptr;
        right = nullptr;
     }
};

// 多叉树节点
struct multinode {
    elemtype data;
    multinode* firstkid;
    multinode* nextbrother;
    int weight;
};
//pq优先是大堆排序，需要修改成小堆排序
struct cmp {
    bool operator()(treenode* a,treenode* b)
    {
        return a->weight > b->weight;
    }
};
constexpr int MAX_SIZE = 100;
//----------------------------------------------------------------复习队列-----------------------------------------------------------------------------------------------
// 模板循环队列
template<typename T>
struct Queue {
    int head;      // 队首下标
    int tail;      // 队尾下标
    int count;     // 元素个数
    T data[MAX_SIZE];

    Queue() : head(0), tail(0), count(0) {}
};

// 入队：const T& 支持临时值
template<typename T>
bool push(Queue<T>& q, const T& val) {
    if (q.count == MAX_SIZE) return false;
    q.data[q.tail] = val;
    q.tail = (q.tail + 1) % MAX_SIZE;
    q.count++;
    return true;
}

// 出队
template<typename T>
bool pop(Queue<T>& q) {
    if (q.count == 0) return false;
    q.head = (q.head + 1) % MAX_SIZE;
    q.count--;
    return true;
}

// 查看队首（通过引用返回）
template<typename T>
bool front(const Queue<T>& q, T& out) {
    if (q.count == 0) return false;
    out = q.data[q.head];
    return true;
}

// 清空队列
template<typename T>
void clear(Queue<T>& q) {
    while (q.count != 0) pop(q);
}
//--------------------------------------------------------树转二叉树-----------------------------------------------------------------------------------------------------
// 多叉树转二叉树
treenode* transform(multinode* root) {
    if (root == nullptr) return nullptr;
    treenode* binNode = new treenode(root->data,root->weight);
    binNode->left = transform(root->firstkid);
    binNode->right = transform(root->nextbrother);
    return binNode;
}
//--------------------------------------------------------------由二叉树生成Haffman树and 编码----------------------------------------------------------------------
//将二叉树分离成个体
void separateTree(vector<treenode*>&trees, treenode* root)
{
   
    if (root == nullptr) return;
    treenode* left = root->left;
    treenode* right = root->right;
    root->left = nullptr;
    root->right = nullptr;
    trees.push_back(root);
    separateTree(trees, left);
    separateTree(trees, right);
}
//构建HMF
treenode* buildHuffmanTree(treenode* root)
{
  
    priority_queue<treenode*, vector<treenode*>, cmp>pq;
    vector<treenode*> trees;
    separateTree(trees, root);
    if (trees.empty()) return nullptr;//防止队首空值出错
    for (treenode* node : trees)
    {
        pq.push(node);
    }
    while (pq.size() >1)
    {
        treenode* left = pq.top();pq.pop();
        treenode* right = pq.top();pq.pop();
        treenode* cur = new treenode(-1, left->weight + right->weight);
        cur->left = left;
        cur->right = right;
        pq.push(cur);
    }
    return pq.top();//返回根节点
}
//哈夫曼树的路径编码
void HuffmanTreeCode(treenode* root)
{
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        if (root->code == "") root->code = "0";
        return;
    }
    if (root->left) {
        root->left->code = root->code + "0";
        HuffmanTreeCode(root->left);
    }
    if (root->right) {
        root->right->code = root->code + "1";
        HuffmanTreeCode(root->right);
    }
}
//打印哈夫曼code
void PrintHuffmanCode(treenode* root)
{
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        cout << "该叶子节点 data = " << root->data
            << "，weight = " << root->weight
            << "，编码值是: " << root->code << endl;
        return;
    }
    PrintHuffmanCode(root->left);
    PrintHuffmanCode(root->right);
}
//-----------------------------------------------------------------------层序遍历BFS----------------------------------------------------------------------------------
void BFS(treenode* root) {
    if (root == nullptr) return;
    Queue<treenode*> q;
    push(q, root);
    while (q.count != 0) {
        treenode* cur;
        if (front(q, cur)) {
            pop(q);
          cout << "该节点 data = " << cur->data
              << "，weight = " << cur->weight<< endl;
            if (cur->left) push(q, cur->left);
            if (cur->right) push(q, cur->right);
        }
    }
}
//--------------------------------------------------------------------用stack完成DFS遍历------------------------------------------------------------------------------
void preorder(treenode* root)
{
    if (root == nullptr) return;
    stack<treenode*> trees;
    trees.push(root);
    while (trees.size() != 0)
    {
        treenode* cur = trees.top();trees.pop();
        cout << cur->data << " ";
        if (cur->right) trees.push(cur->right);
        if (cur->left) trees.push(cur->left);
   }

}

int main() {
    // 构建多叉树
    multinode n6{ 6, nullptr, nullptr,1 };
    multinode n5{ 5, nullptr,  &n6,2 };
    multinode n4{ 4, nullptr, nullptr,3 };
    multinode n3{ 3, nullptr, nullptr ,4};
    multinode n2{ 2, &n5, &n3 ,5};
    multinode n1{ 1, &n2, nullptr ,6};
    n3.nextbrother = &n4;
    treenode* binRoot = transform(&n1);
//先打印二叉树的
    cout << "DFS遍历结果: ";
    preorder(binRoot);
    cout << endl;
//打印哈夫曼树
    treenode* Huffman = buildHuffmanTree(binRoot);
    cout << "BFS 层序遍历结果: ";
    BFS(Huffman);
    cout << endl;
    HuffmanTreeCode(Huffman);
    PrintHuffmanCode(Huffman);
    return 0;
}
//注意力扣 LeetCode补不足
