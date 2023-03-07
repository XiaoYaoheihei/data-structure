#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H
//节点类的实现

class Node
{
    private:
        int node_level;//结点所在层级
    public:
        int key;
        Node **forward;   
        //表示的是指针数组
        //forward数组存储的是当前结点在第i层的下一个结点
        Node(int key, int level);
        ~Node();
        int getkey() const;
};

//构造一个节点
Node::Node(int key, int level) {
    this->key = key;
    
    forward = new Node*[level+1];
    //为forward申请空间
    memset(forward, 0, sizeof(Node*)*(level+1));
}

Node::~Node() {
    delete[]forward;
}

//获取key值
// template<typename K, typename V>
// Node::getkey() const {
//     return key;
// }

#endif