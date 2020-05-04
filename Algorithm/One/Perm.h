#ifndef PERM_H
#define PERM_H

#include <iostream>

//
// swap value
//

template <typename T>
void Swap(T& a, T& b)
{
    T temp=a;
    a=b;
    b=temp;
}

//
// 输出一个数组中所有元素的排序序列
//

template <class T>
void Perm(T List[], int k, int m)    // 生成List[k:m]的所有排列方式
{
    if(k==m){
        for(int i=0; i<=m; i++){
            std::cout << List[i];
        }
        std::cout << std::endl;
    }

    for(int i=k;i<=m; i++){
        Swap(List[k], List[i]);
        Perm(List, k+1, m);
        Swap(List[k], List[i]);
    }
}

#endif
