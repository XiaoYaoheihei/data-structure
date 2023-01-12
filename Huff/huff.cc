#include "huff.h"
using namespace std;

int main() {
    char handle, choice;
    bool back = true;
    //循环进行想要的操作
    while (back) {
        cout << "********Welcome to use the Huffman Encoding System!!!********" << endl;
		cout << "\t" << "I-----Initialization(初始化、建立哈夫曼树)" << endl;
		cout << "\t" << "T-----Tree printing(打印哈夫曼树)" << endl;
		cout << "\t" << "C-----Huffman code printing(打印哈夫曼编码)" << endl;
		cout << "\t" << "E-----Encoding(编码)" << endl;
		// cout << "\t" << "P-----Print(打印编码文件)" << endl;
		cout << "\t" << "D-----Decoding(译码)"  << endl;
        cout << "\t" << "S-----Static(统计文本文件)" << endl;
		cout << "\t" << "Q-----Quit(退出)" << endl;
		cout << endl;
 
		cout << "请输入您想进行的操作： ";
		cin >> handle;
        switch (handle) {
        case 'I': {
            Init();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        case 'T': {
            if (HfmTree == NULL) {
                //如果刚开始的哈夫曼树并没有通过手动建立
                //通过读取文件中的数据对哈夫曼树的相关数据进行初始化
                InitByFile();
            }
            PrintHufTree();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        case 'C': {
            if (HfmTree == NULL) {
                //如果刚开始的哈夫曼树并没有通过手动建立
                //通过读取文件中的数据对哈夫曼树的相关数据进行初始化
                InitByFile();
            }
            PrintCodeString();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        case 'E': {
            if (HfmTree == NULL) {
                //如果刚开始的哈夫曼树并没有通过手动建立
                //通过读取文件中的数据对哈夫曼树的相关数据进行初始化
                InitByFile();
            }
            Encoding();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        case 'D': {
            if (HfmTree == NULL) {
                //如果刚开始的哈夫曼树并没有通过手动建立
                //通过读取文件中的数据对哈夫曼树的相关数据进行初始化
                InitByFile();
            }
            Decoding();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        case 'Q':
            exit(1);
        case 'S': {
            StaticFile();
            cout << "是否返回主菜单? Y/N" << endl;
            cin >> choice;
            if (choice == 'Y') back = true;
            else exit(1);
            break;
        }
        }
    }
}