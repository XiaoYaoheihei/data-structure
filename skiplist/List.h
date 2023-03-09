#ifndef SKIPLIST_LIST_H
#define SKIPLIST_LIST_H

#include "Node.h"


class SkipList {
    private:
        int level;//当前层数
        int MAXLVL;
        //跳表的最大层数
        float p;

        //注意:这里要声明成Node<K,V>而不是Node,否则编译器会把它当成普通的类
        Node *head;//跳表的头结点
        //Node<K, V> *tail;//跳表的尾结点

    public:
        //初始化表,初始化的时候初始化最大level
        SkipList(int level, float);
        //释放表
        void freeList();
        //展示表中各结点的level以及key
        void display();

        //创建一个新的结点，结点的层数为leveL
        Node* creatNode(int key, int level);
        //随机生成一个level
        int getRandomLevel();
        //插入一个元素
        void insertElement(int key);
        //删除元素
        void deleteElement(int key);
        //查找元素
        void searchElement(int key);

};

#endif 