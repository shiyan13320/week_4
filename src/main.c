#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "SeqStack.c"
#include "SeqStack.h"
#include "WriteCompound.c"
#include "WriteCompound.h"

#define MAX_EXP 80

typedef long long DATA;

/* 判断是否为运算符，是返回1，不是返回0 */
int IsOperator (char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

/*判断两个运算符的优先级，oper1>oper2返回1,oper1<oper2返回-1*/
int PRI (char oper1, char oper2) {
    int pri;
    switch (oper2) {
    case '+':
    case '-':
        if (oper1 == '=') {
            pri = -1;
        } else {
            pri = 1;
        }
        break;
    case '*':
    case '/':
    case '%':
        if (oper1 == '*' || oper1 == '/' || oper1 == '%') {
            pri = 1;//oper1>oper2
        } else {
            pri = -1;
        }
        break;
    case '=':
        pri = 1;
        break;
    }
    return pri;
}

/* 计算两个操作数的结果 */
long long Calc (long long a, int oper, long long b) {
    switch (oper) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b != 0) {
            return a / b;
        } else {
            printf("分子不能为0！\n");
            exit(0);
        }
    case '%':
        if (b != 0) {
            return a % b;
        } else {
            printf("分子不能为0！\n");
            exit(0);
        }
    }
}

long long CalcExp(char StrExp[]) {
    SeqStack *StackOper, *StackData;
    int i = 0;

    /* flag用以处理多位数，while中每次从表达式中取一个字符，
    flag=0时：操作数已入栈；flag=1时：有操作数要入栈 */
    int flag = 0;
    DATA a, b, c, q, x, t, oper;

    StackOper = Init_SeqStack();
    StackData = Init_SeqStack();

    q = 0;
    x = '=';
    Push_SeqStack(StackOper, x);
    c = StrExp[i++];

    while (c != '=' || x != '=') {
        if (IsOperator(c)) {
            if (flag) {
                Push_SeqStack(StackData, q);
                q = 0;
                flag = 0;
            }
            switch(PRI(x, c)) {
            case -1:
                Push_SeqStack(StackOper, c);
                c = StrExp[i++];
                break;
            case 1:
                oper = Pop_SeqStack(StackOper);
                b = Pop_SeqStack(StackData);
                a = Pop_SeqStack(StackData);
                t = Calc(a, oper, b);
                Push_SeqStack(StackData, t);
                break;
            }
        } else if (c >= '0' && c <= '9') {
            c -= '0';
            q = q * 10 + c;
            flag = 1;
            c = StrExp[i++];
        } else {
            printf("input wrong!\n");
            exit(0);
        }
        x = Top_SeqStack(StackOper);
    }
    q = Pop_SeqStack(StackData);
    free(StackData);
    free(StackOper);
    return q;
}

int main() {
    long long result;
    char StrExp[MAX_EXP];

    while (1) {
        printf("Please input expression（“=”end）:\n");
        scanf("%s", StrExp);
        result = CalcExp(StrExp);
        printf("%lld\n", result);
        sprintf(StrExp, "%s%lld\n", StrExp, result);

        Write_Result(sizeof(StrExp), StrExp);
    }
    return 0;
}
