#include <iostream>

using namespace std;

template <typename T>
class BST {
  private:
    struct Node {
      T value;
      Node* left;
      Node* right;
    };

    Node* root;

    //清楚BST树中的所有节点
    Node* makeEmpty(Node* t) {
      if (t == NULL) return NULL;
      makeEmpty(t->left);
      makeEmpty(t->right);
      //左右子树都释放完之后释放该节点
      delete t;
      return NULL;
    }

    Node* insert(Node* t, T x) {
      if (t == NULL) {
        //只是在叶子节点建立节点
        t = new Node;
        t->value = x;
        t->left = NULL;
        t->right = NULL;
      } else if (x < t->value) {
        //递归建立左子树
        t->left = insert(t->left, x);
      } else if (x > t->value) {
        //递归建立右子树
        t->right = insert(t->right, x);
      }
      return t;
    }

    Node* remove(Node* t, T x) {
      Node* tmp;
      if (t == NULL) {
        return NULL;
      } else if (x < t->left) {
        t->left = remove(t->left, x);
      } else if (x > t->right) {
        t->right = remove(t->right, x);
      } else if (t->left && t->right) {
        //找到了待删除的节点，此时待删除的节点不是叶子节点
        //左右子树都不为空
        //默认找右子树的最小节点,替换为当前的节点
        tmp = findMin(t->right);
        t->value = tmp->value;
        //删除掉右子树的最小节点
        t->right = remove(t->right, tmp->value);
      } else {
        //两种情况：1.左右子树有一个空节点
        //2.删除的是叶子节点
        tmp = t;
        if (t->left == NULL) {
          t = t->right;
        } else if (t->right == NULL) {
          t = t->left;
        }
        delete tmp;
      }
      return t;
    }

    Node* find(Node* t, T x) {
      if (t == NULL) return NULL;
      if (x < t->value) 
        //递归的左边查找
        return find(t->left, x);
      else if (x > t->value)
        //递归的右边查找 
        return find(t->right, x);
      //找到了对应的元素之后返回节点即可
      return t;
    }

    Node* findMin(Node* t) {
      //只关心左子树
      if (t == NULL || t->left == NULL) {
        return t;
      }
      //递归寻找最小节点
      return findMin(t->left);
    }

    Node* findMax(Node* t) {
      //只关心右子树
      if (t == NULL || t->right == NULL) {
        return t;
      }
      //递归寻找最大节点
      return findMax(t->right);
    }

  public:
    BST() : root(NULL) {}

    ~BST() {
      //释放掉BST树中的所有节点
      makeEmpty(root);
    }

    void Insert(T x) {
      insert(root, x);
    }

    void Remove(T x) {
      remove(root, x);
    }

    void Find(T x) {
      find(root, x);
    }
};

//测试
int main() {


  return 0;
}
