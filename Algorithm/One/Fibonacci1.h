#ifndef FIBONACCI_ONE
#define FIBONACCI_ONE

#include <iostream>

int Fibonacci(int n)
{
    if(n<=0)
        return 0;
    if(n==1){
        return 1;
    }
    return Fibonacci(n-1) + Fibonacci(n-2);
}

#endif
