#ifndef FIND_X
#define FIND_X

template <typename T>
bool FindX(T List[], int k, int m, T value)
{
    if(k>=m+1)
        return false;

    if(List[k]==value)
        return true;
    else
        FindX(List, k+1, m, value);
}

#endif
