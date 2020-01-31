#include<iostream>
#include<cmath>

#include "operators.hpp"

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b){ 
    return a - b;
}

int mult(int a, int b){ 
    return a * b;
}

int divide(int a, int b) {
    return floor((double) a / (double) b);
} 

int modulo(int a, int b){
    int c = a - divide(a, b) * b;
    if (c < 0 ){
        return -c;
    }else{
        return c;
    }
} 

int pwr(int a, int b){
    return pow(a, b);
}

int neg(int a){
    return -a;
}