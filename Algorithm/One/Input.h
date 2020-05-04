#ifndef INPUT_H
#define INPUT_H

#include <iostream>

//
// 检测输入
//

template <typename T>
bool Input(T &data)
{
    T buf;
    bool ret = false;
    for(int i=0; i<3; i++){
        std::cout << "请输入一个非负数：";
        std::cin >> buf;
        if(buf >=0 ){
            data = buf;
            ret = true;
            break;
        }
        else{
            std::cout << "输入非法，请重新输入！" << std::endl;;
        }
    }

    return ret;
}

#endif
