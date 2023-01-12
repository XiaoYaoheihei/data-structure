#ifndef HUFF_H
#define HUFF_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unistd.h>
#define INT_MAX 4096
#define MAX 1024
using namespace std;

//哈夫曼树的结点类型
struct HufNode {
    int LeftChild, RightChild, Parent;
    double weight;
    HufNode() : Parent(0), weight(0.0) { }
};

int hfmSize = 0;            //哈夫曼树的规模

char *characters = NULL; //字符集
double *weight = NULL;   //权值
string *HuffmanCodeStrings = NULL;   //字符集对应的哈夫曼编码
HufNode* HfmTree = NULL;             //结构体数组形式的哈夫曼树

void PrintLine() {
    cout << "--------------------------------------" << endl;
}


//从哈夫曼树的n个结点中选出权值最小的结点，并返回该结点的索引
int MinInhuffmanTree(HufNode hfmTree[], int n)
{
	int minIndex = 0;
	int minWeight = INT_MAX;
 
    //利用插入排序的思想进行最小结点和最小权值的赋值
	for (int i = 1; i <= n; i++) {
        //一定必须得有两个判断条件，必须是在父结点为0的结点中寻找
		if (hfmTree[i].weight < minWeight && hfmTree[i].Parent == 0) {
			minWeight = hfmTree[i].weight;
			minIndex = i;
		}
	}
    //设置其parent为1，表示该结点已经“使用过”
	hfmTree[minIndex].Parent = 1; 
	return minIndex;
}

//从哈夫曼树的n个结点中选出权值最小的两个结点，并通过引用带回对应的索引
void SelectTwoMinsFromhfmTree(HufNode HfmTree[], int n, int& min1, int& min2) {
    min1 = MinInhuffmanTree(HfmTree, n);
	min2 = MinInhuffmanTree(HfmTree, n);
    //始终保证左孩子比右孩子小
	//使得min1保存权值最小的两个结点hfmTree[min1], hfmTree[min2]中最小的索引
	if (min1 > min2) swap(min1, min2);
}
//通过建立哈夫曼树得到字符集的相应哈夫曼编码
void HuffCoding(HufNode HfmTree[], string HuffmanCodeStrings[], double weight[], int n) {
    int min1, min2;
    if (n <= 1) return;
    int m = 2 * n - 1;      //所有的结点数

    //初始化所有叶子结点
    for (int i = 1; i <= n; i++) {
        HfmTree[i].weight = weight[i];
		HfmTree[i].Parent = HfmTree[i].LeftChild = HfmTree[i].RightChild = 0;
    }
    //初始化除了叶子结点之外的结点
    for (int i = n + 1; i <= m; i++) 
        HfmTree[i].Parent = 0;
    //对除了叶子结点之外的结点进行赋值操作
    for (int i = n + 1; i <= m; i++) {
        SelectTwoMinsFromhfmTree(HfmTree, i - 1, min1, min2);
        //标记访问过的两个叶子结点的父亲结点
		HfmTree[min1].Parent = HfmTree[min2].Parent = i;
		HfmTree[i].LeftChild = min1;
		HfmTree[i].RightChild = min2;
		HfmTree[i].weight = HfmTree[min1].weight + HfmTree[min2].weight;
    }

    //从哈夫曼树的n个叶节点出发，自底向上沿着通往根结点的路径，最终分别得到n个不同字符对应的哈夫曼编码
    int parent, current;
    for (int i = 1; i <= n; i++) {
        string codestring = "";
        int length = 0;
        current = i;
        parent = HfmTree[current].Parent;
        while (parent != 0) {
            //分别判断左右孩子的情况,左孩子0+，右孩子1+
            if (HfmTree[parent].LeftChild == current)
                codestring = '0' + codestring;
            else 
                codestring = '1' + codestring;
            //一层一层向根节点访问
            current = parent;
            parent = HfmTree[current].Parent;
        }
        HuffmanCodeStrings[i] = codestring;
    }
}

//通过读取文件中的数据对哈夫曼树的相关数据进行初始化
void InitByFile() {
    ifstream in("HfmTree.txt", ios::in | ios::binary);
	if (!in.is_open()) {
		cerr << "文件HfmTree.txt打开失败！" << endl;
		return;
	}
    //一定要先从文件中读取哈夫曼树的大小
    in.read((char*)&hfmSize, sizeof(int));
    cout << hfmSize << endl;
    //设置起始下标
    int m = 2 * hfmSize - 1;
    characters = new char[hfmSize+1];
    weight = new double[hfmSize+1];
    HuffmanCodeStrings = new string[hfmSize+1];

    HfmTree = new HufNode[m+1];   //树中的结点总数

    in.read(characters, sizeof(char)*(hfmSize + 1));
	cout << "读取成功" << endl;
    // for (int i = 1; i <= hfmSize; i++) cout << characters[i] << "  ";
    in.read((char*)weight, sizeof(double)*(hfmSize + 1));
	// cout << weight << endl;
    in.read((char*)HuffmanCodeStrings, sizeof(string)*(hfmSize + 1));
	// cout << HuffmanCodeStrings << endl;
    in.read((char*)HfmTree, sizeof(HfmTree[0])*(m + 1));
    // cout << characters << " " << weight << "  " << HuffmanCodeStrings << endl;
	in.close();
}

//初始化并且建立哈夫曼树
void Init() {
    int num;
    cout << "请输入所要编码的字符种类个数" << endl;
    cin >> num;
    hfmSize = num;  //规模进行赋值

    //0号下标不使用，从1开始
    characters = new char[num+1];
    weight = new double[num+1];
    HuffmanCodeStrings = new string[num+1];

    HfmTree = new HufNode[2*num];   //树中的结点总数
    cout << "按照顺序输入每种字符以及对应的权值" << endl;
    PrintLine();

    char now;   //字符
    for (int i = 1; i <= num; i++ ) {
        cout << "第" << i << "个字符" << endl;
        cin >> now;
        characters[i] = now;
        cout << "请输入该字符对应的权值" << endl;
        cin >> weight[i];
        PrintLine();
    }
    cout << "字符集为" << endl;
    for (int i = 1; i <= num; i++) {
        cout << characters[i] << ":" << weight[i] << endl;
    }
    cout << endl;
    PrintLine();

    //得到字符集的哈夫曼编码
    HuffCoding(HfmTree, HuffmanCodeStrings, weight, num);
    PrintLine();

    //将各种字符的哈夫曼编码存入到文件当中去
    cout << "下面将各种字符的哈夫曼编码写入文件hfmTree.txt中......" << endl;
    ofstream out("HfmTree.txt", ios::out | ios::binary);
    if (!out.is_open()) {
        cerr << "文件HfmTree.txt打开失败" << endl;
        exit(1);
    }

    out.write((char*)&hfmSize, sizeof(int));//写入哈夫曼树的大小
    out.write((char*)characters, sizeof(char)*(hfmSize+1));//写入字符集
    out.write((char*)weight, sizeof(double)*(hfmSize+1));//写入权值
    out.write((char*)HuffmanCodeStrings, sizeof(string)*(hfmSize+1));//字符集对应的哈夫曼编码
    out.write((char*)HfmTree, sizeof(HfmTree[0])*(2*num));//哈夫曼的结构体形式

    cout << "写入文件HfmTree.txt成功" << endl;
    out.close();
}
//递归进行打印的函数
char branches[] = {" /\\<" };
void printtree(int root, int height, ostream& out) {
    if (root != 0) {
        //先打印右子树,深度+1
        printtree(HfmTree[root].RightChild, height+1, out);
        //通过跳格符来表现当前节点的深度，深度越大的结点会越往右
        for (int i = 0; i < height; i++) {
            out << "\t";
        }
        out << HfmTree[root].weight;//输出当前结点的权值
        
        if (HfmTree[root].LeftChild == 0 && HfmTree[root].RightChild == 0)
            out << "(" << characters[root] << ")";
        //打印树枝
        out << branches[((HfmTree[root].LeftChild != 0) << 1) | (HfmTree[root].RightChild != 0)];
        //换行，打印当前结点的左子树
        out << endl;
        printtree(HfmTree[root].LeftChild, height+1, out);
        }
        // for (int i = 0; i < height; i++) 
        //     out << "\t";
    }

//打印哈夫曼树
void PrintHufTree() {
    cout << "该哈夫曼树打印的结果如下所示" << endl;
    cout << "hfmSize == " << hfmSize << endl;
    printtree(2*hfmSize-1, 0, cout);
    cout << endl;
    //并且将打印的结果存入到文件当中去
    ofstream now("TreePrint.txt", ios::out);
    if (!now.is_open()) {
        cerr << "TreePrint.txt打开失败" << endl;
        exit(1);
    }
    printtree(2*hfmSize-1, 0, now);
    cout << "TreePrint.txt写入成功" << endl;
    now.close();
}

//打印字符集的哈夫曼编码
void PrintCodeString() {
    cout << "字符集的编码如下" << endl;
    for (int i = 1; i <= hfmSize; i++) {
        cout << "字符" << characters[i] << endl; 
        cout << "(权值为" << weight[i] << ")" << endl; 
        cout << ":" << HuffmanCodeStrings[i] << endl;
    }
}
//对文本进行编码
void Encoding() {
    string choice, TextToBeEncode, EncodString;
    string ch;
    cout << "您有如下两种方式提供待编码文本:" << endl << endl;
	cout << "1-----读取文件BeTranslate.txt中的待编码文本;" << endl;
	cout << "2-----读取实时输入的待编码文本；" << endl;
	PrintLine();
	cout << "您选择方式： " << endl;
	cin >> choice;
    if (choice == "1") {
        char ch;
        //以读的方式打开待编码文件
        ifstream In("ToBeTran.txt", ios::in);
        if (!In.is_open()) {
            cerr << "文件ToBeTran.txt打开失败" << endl;
            exit(1);
        }
        
        ofstream Out("CodeFile.txt", ios::out);
        if (!Out.is_open()) {
            cerr << "文件CodeFile.txt打开失败" << endl;
            exit(1);
        }

        //读取文件中的所有字符信息并进行编码
        while ((ch = In.get()) != EOF) {
            TextToBeEncode = TextToBeEncode + ch;
        }
        for (int i = 0; i < TextToBeEncode.length(); i++) {
            for (int j = 1; j <= hfmSize; j++) {
                if (characters[j] == TextToBeEncode[i]) 
                    EncodString = EncodString + HuffmanCodeStrings[j];
                }
        }
        //将编码成功的字符写入到文件当中去
        Out << EncodString;
        cout << "该段文本被编码后写入文件CodeFile.txt成功!" << endl;

        In.close();
        Out.close();
    } else if (choice == "2") {
        cout << "请输入您的待编码文件" << endl;
        cin >> ch;
        // while (cin.get(ch) && ch != '\n') {
            TextToBeEncode = TextToBeEncode + ch;
        // }
        for (int i = 0; i < TextToBeEncode.length(); i++) {
            for (int j = 1; j <= hfmSize; j++) {
                if (characters[j] == TextToBeEncode[i])
                    EncodString = EncodString + HuffmanCodeStrings[j];
            }
        }
        cout << "该文本的编码如下:" << endl;
        cout << EncodString << endl;
    }
}

//对文本进行译码
void Decoding() {
    string choice,TextToBeDecode, DecodString;
    string ch;
    cout << "您有如下两种方式提供待译码文本:" << endl << endl;
	cout << "1-----读取文件CodeFile.txt中的待译码文本;" << endl;
	cout << "2-----读取实时输入的待译码文本；" << endl;
	PrintLine();
	cout << "您选择方式： " << endl;
	cin >> choice;
    if (choice == "1") {
        char ch;
        ifstream In("CodeFile.txt", ios::in);
        if (!In.is_open()) {
            cerr << "文件CodeFile.txt打开失败" << endl;
            exit(1);
        }
        ofstream Out("TextFile.txt", ios::out);
        if (!Out.is_open()) {
            cerr << "打开文件TextFile.txt失败" << endl;
            exit(1);
        }

        while((ch = In.get()) != EOF) {
            TextToBeDecode = TextToBeDecode + ch;
        }
        //首先定位到根节点
        int m = 2 * hfmSize - 1;
        for (int i = 0; i < TextToBeDecode.length(); i++) {
            if (TextToBeDecode[i] == '0') {
                //从根节点的左孩子开始访问
                m = HfmTree[m].LeftChild;
                if (HfmTree[m].LeftChild /*== HfmTree[m].RightChild*/ == 0) {
                    DecodString = DecodString + characters[m];
                    //重新定位到根节点
                    m = 2 * hfmSize - 1;
                }

            } else if (TextToBeDecode[i] == '1') {
                //从根节点的右孩子开始访问
                m = HfmTree[m].RightChild;
                if (HfmTree[m].LeftChild /*== HfmTree[m].RightChild */== 0) {
                    DecodString = DecodString + characters[m];
                    m = 2 * hfmSize - 1;
                }
            }
        }
        cout << DecodString << endl;
        Out << DecodString;
        cout << "该段文本被译码后写入文件TextFile.txt成功!" << endl;

        In.close();
        Out.close();
        
    } else if (choice == "2") {
        cout << "请输入您的待译码文本" << endl;
        cin.get();
        cin >> ch;
        // while (cin.get(ch) && ch != '\n') {
            TextToBeDecode = TextToBeDecode + ch;
        // }
        //首先定位到根节点
        int m = 2 * hfmSize - 1;
        for (int i = 0; i < TextToBeDecode.length(); i++) {
            if (TextToBeDecode[i] == '0') {
                //从根节点的左孩子开始访问
                m = HfmTree[m].LeftChild;
                if (HfmTree[m].LeftChild /*== HfmTree[m].RightChild */== 0) {
                    DecodString = DecodString + characters[m];
                    //重新定位到根节点
                    m = 2 * hfmSize - 1;
                }

            } else if (TextToBeDecode[i] == '1') {
                //从根节点的右孩子开始访问
                m = HfmTree[m].RightChild;
                if (HfmTree[m].LeftChild /*== HfmTree[m].RightChild*/ == 0) {
                    DecodString = DecodString + characters[m];
                    m = 2 * hfmSize - 1;
                }
            }
        }
        cout << "该段文本被译码为如下：" << endl;
		cout << DecodString << endl;
    }
}


//c++统计文本文件
// void StaticFile() {
//     cout << "正在打开file.txt....." << endl;
//     // sleep(3);
//     ifstream in;
//     in.open("file.txt");
//     // if (!in.is_open()) {
//     //     cerr << "文件打开失败" << endl;
//     //     exit(1);
//     // }
//     char ch;
//     char word[MAX];
//     int i = 0, n = 0;
//     //使用简单的桶排序
//     while((ch = in.get()) != EOF) {
//         word[i++] = ch;
//         cout << word[i] << " ";
//     }
//     int number[MAX] = {0};
//     for(int j = 0; j < MAX; j++) {
//         number[word[j]]++;
//     }
//     for (int j = 0; j < MAX; j++) {
//         if (number[j] != 0) 
//             n++;
//     }
//     if (n != 0) {
//         cout << "字符的个数为:";
//         cout << n << endl;
//     }
//     in.close();
// }

//c统计文件中字符个数
void StaticFile() {
    FILE *fp = fopen("file.txt", "r");
    if (fp == NULL) {
        exit(1);
    }
    int count = 0;
    char ch;
    int source[MAX] = {0};
    int i = 0;
    while ((ch =fgetc(fp)) != EOF) {
       count++;
       source[i++] = ch;
    }
    // cout << "赋值成功" << endl;
    int number[MAX] = {0};
    for(int j = 0; j < MAX; j++) {
        //这里不加条件判断的话会有整型溢出的问题
        if (source[j] == 0) break;
        cout << j << " " << source[j] << endl;
        number[source[j]]++;
    }
    // cout << "计算成功" << endl;
    int n = 0;
    for(int k = 0; k < MAX; k++) {
        if (number[k] != 0) {
            n++;
        }
    }
    fclose(fp);
    cout << "字符个数为：" << endl;
    cout << "count == " << count << endl;
    cout << "字符种类个数为：" << n << endl;
}
#endif 