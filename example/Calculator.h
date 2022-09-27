#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct Polynomial{
    double coefficient;
    int index;
    struct Polynomial *next;
}Polynomial,*Poly;
typedef struct List{
    char name;
    Polynomial *next;
}List,*ListP;

//判断一行输入是否为整数，是则返回该整数，否则返回0
int IsNumber(char *s);

//判断一行输入是否为数字，是则返回该数字，否则返回ERROR
Status IsDouble(char *s,double &num);

//逐项输入多项式A/B
Status SimpleEstablish(List *P,int t);

//类数学表达式输入多项式A/B
Status MathEstablish(List *P,int t);

//销毁多项式A/B/R
Status DestroyPolynomial(List *P,int i);

//以n, c1,e1, c2,e2, ..., cn,en的格式输出多项式A/B/R
Status SimpleOutput(List *P,int i);

//整理多项式，合并同类项，并以指数由大到小排序
Status ArrangePolynomial(List *P,int i);

//以类数学表达式的格式输出多项式A/B/R
Status MathOutput(List *P,int i);

//计算A+B，结果存入R
Status Plus(List *P);

//计算A-B，结果存入R
Status Minus(List *P);

//计算f(x)，结果直接返回
double Calculate(List *P,int i);

//计算A'/B'，结果存入R
Status Derivative(List *P,int i);

//计算A*B，结果存入S
Status Multiply(List *P);

#endif