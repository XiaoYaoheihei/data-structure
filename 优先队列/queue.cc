#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// int main() {
//     //默认的是大顶堆
//     priority_queue<int> a;
//     //小顶堆
//     priority_queue<int, vector<int>, greater<int> > c;
//     priority_queue<string> b;

//     for (int i = 0; i < 5; i++) {
//         a.push(i);
//         c.push(i);
//     }
//     while (!a.empty()) {
//         std::cout << a.top() << " ";
//         a.pop();
//     }
//     std::cout << endl;
//     while (!c.empty()) {
//         std::cout << c.top() << " ";
//         c.pop();
//     }
//     std::cout << endl;

//     b.push("abc");
//     b.push("abcd");
//     b.push("cbd");
//     while (!b.empty()) {
//         std::cout << b.top() << " ";
//         b.pop();
//     }
//     std::cout << endl;
// }


struct tmp2 //仿函数
{
    bool operator() (int a, int b)
    {
        return a > b; //小顶堆
        //return a < b;大顶堆
    }
};

int main()
{
    priority_queue<int, vector<int>, tmp2 > b;
    for (int i = 0; i < 5; i++) {
        b.push(i);
    }
    while(!b.empty()) {
        std::cout << b.top() << " ";
        b.pop();
    }
    std::cout << endl;
}
