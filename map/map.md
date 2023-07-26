### cpp——map

cpp中的map使用的是**红黑树**进行元素查找的。

map保证了元素的有序性，是按照**键值排序**的。

前向迭代器保证顺序是从小到大输出，反向迭代器保证顺序从大到小输出。

```c++
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> myMap;

    // 向 map 中插入多个键值对
    myMap.insert({1, "apple"});
    myMap.insert({2, "banana"});
    myMap.insert({3, "orange"});
    myMap.insert({4, "pear"});
    myMap.insert({5, "grape"});

    // 使用双向迭代器遍历 map，并输出所有的键值对
    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }

    for (auto it = myMap.rbegin(); it != myMap.rend(); it++) {
        std::cout << it->first << "," << it->second << std::endl;
    }
    return 0;
}
```



### cpp——unorded_map和unorded_multimap

cpp中的unorded_map使用的是**哈希索引**进行元素查找。

unorded_map使用**开放定址法**解决哈希冲突。

他不允许有多个相同的key,如果插入了多个相同的key,后插入的会覆盖掉先前插入的key-value。

使用unorded_multimap可以存储多个重复的key。

**元素查找的时候找到返回一个迭代器，此迭代器指向相应的键值，没找到就返回map尾部的迭代器。**

```c++
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // 定义一个 std::unordered_map，键为学生的学号，值为学生的姓名
    std::unordered_map<int, std::string> studentMap;

    // 插入一些学生信息
    studentMap[101] = "Alice";
    studentMap[102] = "Bob";
    studentMap[103] = "Charlie";
    studentMap[104] = "David";
    studentMap[105] = "Emily";

    // 查找学号为 103 的学生的姓名
    int targetID = 103;
    auto it = studentMap.find(targetID);

    if (it != studentMap.end()) {
        std::cout << "Student with ID " << targetID << " is " << it->second << std::endl;
    } else {
        std::cout << "Student with ID " << targetID << " not found." << std::endl;
    }

    std::unordered_multimap<int, std::string> myMultimap;

    // 向 unordered_multimap 中插入多个相同的键，每个键对应一个值
    myMultimap.insert({1, "apple"});
    myMultimap.insert({2, "banana"});
    myMultimap.insert({1, "orange"});
    myMultimap.insert({3, "pear"});
    myMultimap.insert({1, "grape"});
    myMultimap.insert({2, "mango"});

    // 使用迭代器遍历 unordered_multimap，并输出所有的键值对
    for (auto it = myMultimap.begin(); it != myMultimap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }

    return 0;
}
```



### go——map

go的map也使用的是哈希索引进行元素查找，但是go的map底层利用开放寻址的方式解决哈希冲突。

当容量达到一定的时候，map会自动扩容。

他的map是无序的，遍历map会无序输出。

```go
package main

import "fmt"

func main() {
	// 创建一个 map，键是字符串类型，值是整数类型
	myMap := make(map[string]int)

	// 向 map 中插入多个键值对
	myMap["apple"] = 1
	myMap["banana"] = 2
	myMap["orange"] = 3
	myMap["pear"] = 4
	myMap["grape"] = 5

	// 使用 for-range 遍历 map，并输出所有的键值对
	for key, value := range myMap {
		fmt.Printf("Key: %s, Value: %d\n", key, value)
	}
}
```

