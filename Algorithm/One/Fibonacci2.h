#ifndef FIBONACCI_TWO_H
#define FIBONACCI_TWO_H

int Fibonacci(int n)
{
    int a=0;
    int b=1;
    while(n>0){
        b=a+b;
        a=b-a;
        n--;
    }
    return a;

}

#endif
