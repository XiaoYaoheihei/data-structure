#include "List.h"
#include "Node.h"
#include <bits/stdc++.h>
using namespace std;

//初始化表
SkipList::SkipList(int MAXLVL, float p) {
    this->MAXLVL = MAXLVL;
    this->p = p;
    
    level = 0;
    head = new Node(-1, MAXLVL);
    //初始化一个头结点并给赋值为-1
}

//为结点创建随机级别（level）
//问题是如何为结点创建随机level？？？？这个p的意义又是什么呢？？？
int SkipList::getRandomLevel() {
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while (r < p && lvl < MAXLVL){
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
}

//表中初始化一个node
Node* SkipList::creatNode(int key, int level) {
    Node *now = new Node(key, level);
    return now;
}

//插入元素
void SkipList::insertElement(int key) {
    Node *current = head;
    //从头结点开始遍历

    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));
    //初始化一个更新array
    //这里 update[i] 保存指向级别 i 的节点的指针，
    //我们从该级别向下移动到级别 i-1 和节点的指针向左指向级别 0 的插入位置。

    //从skiplist中的最高级别的结点开始遍历
    //当键大于当前节点下一个节点的键时，向前移动当前指针;
    //下一个节点的键大于要插入的键，然后我们将指向当前节点 i 的指针
    //存储在 update[i] 并向下移动一级并继续我们的搜索。
    for (int i = level; i >= 0; i--) {
        while(current->forward[i] != NULL && 
              current->forward[i]->key < key) {
                current = current->forward[i];
              }
        update[i] = current;
    }

    //找到插入位置之后
    //重新返回级别0并将指针指向右侧
    current = current->forward[0];

    //如果 current 为 NULL，这意味着我们已经到达关卡的末尾，
    //或者当前的键不等于要插入的键，这意味着我们必须在 update[0] 
    //和当前节点之间插入节点
    if (current == NULL || current->key != key) {
        //产生一个随机level
        int rlevel = getRandomLevel();
        
        //生成的rlevel>level的解决办法是更新level，并把多余的指针部分指向头
        //更新level值的方式是一种解决办法
        //我感觉这样的解决方式不是最佳的，会有空间浪费
        //我觉得可以生成一个范围值，介于0～MAXLVL-1之间
        if (rlevel > level) {
            for(int i = level + 1; i < rlevel + 1; i++) {
                update[i] = head;
            }            
            level = rlevel;
        }

        Node *n = creatNode(key, rlevel);

        for(int i = 0; i <= rlevel; i++) {
            //插入链表结点的基本操作
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "successfully insert key" << key << endl;
    }

}

//展示各个level层的key值
void SkipList::display() {
    cout << "Skip List" << endl;
    for (int i = 0; i <= level; i++) {
        Node *node = head->forward[i];
        cout << "level " << i << ":";
        while (node != NULL) {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
}

//删除元素
void SkipList::deleteElement(int key) {
    Node *current = head;

    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for(int i = level; i >= 0; i--) {
        while(current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    if (current != NULL && current->key == key) {

        for(int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }

            update[i]->forward[i] = current->forward[i];
        }
    }

    //修改表的level值
    while(level > 0 && head->forward[level] == 0) {
        level--;
    }
    cout << "Successfully delete key" << endl;
}

//搜索元素
void SkipList::searchElement(int key) {
    Node *current = head;
    for (int i = level; i >= 0; i--) {
        while(current->forward[i] && current->forward[i]->key < key ) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    if (current && current->key == key) {
        cout << "Found key:" << key << endl;
    }
}