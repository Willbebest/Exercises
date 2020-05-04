#ifndef FACTORIAL_N_H
#define FACTORIAL_N_H

int Factorial(int n){
    int sum=1;
    for(int i=1; i<=n;i++){
        sum*=i;
    }
    return sum;
}

#endif
