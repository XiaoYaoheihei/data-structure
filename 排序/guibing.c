#include <stdio.h>
#include <stdlib.h>
//二路归并排序
void Merge(int *a, int *temp, int left,int mid, int right) {
    //标记左半区第一个未排序的元素
    int l_pos = left;
    //右半区第一个未排序的元素
    int r_pos = mid + 1;
    //临时数组的下标
    int pos = left;

    while(l_pos <= mid && r_pos <= right) {
        if(a[l_pos] < a[r_pos]) //左半区较小
            temp[pos++] = a[l_pos++];
        else 
            temp[pos++] = a[r_pos++]; 
    }
    //左半区有剩余元素
    while(l_pos <= mid) {
        temp[pos++] = a[l_pos++];
    }
    //右半区有剩余元素
    while(r_pos <= right) {
        temp[pos++] = a[r_pos++];
    }
    //临时数组元素复制给原数组
    while(left <= right) {
        a[left] = temp[left];
        left++;
    }
}

void Sort(int *a, int *temp, int left, int right) {
    if (left < right) {
        int mid = (left + right)/2;
        printf("%d\n", mid);
        Sort(a, temp, left, mid);
        Sort(a, temp, mid + 1, right);
        //合并已经排序的部分
        Merge(a, temp, left, mid, right);
    } else {
        return ;
    }
}

void MergeSort(int *a, int n) {
    //临时分配数组
    int *temp = (int *)malloc(sizeof(int)*n);
    //排序执行
    Sort(a, temp, 0, n - 1);
    free(temp);
}

int main() {
    int a[9] = {10, 8, 6, 9, 5, 2, 4, 3, 1};
    //排序入口
    MergeSort(a, 9);
    for(int i = 0 ; i < 9; i++)
        printf("%d  ", a[i]);
    return 0;
}