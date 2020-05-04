#ifndef IS_ASCEN_ORDER_H
#define IS_ASCEN_ORDER_H

template <typename T>
bool IsAscendOrder(T List[], int n)
{
    bool ret = true;
    for(int i=1; i<n; i++){
        if(List[i-1]>List[i]){
            ret=false;
            break;
        }
    }

    return ret;
}

#endif
