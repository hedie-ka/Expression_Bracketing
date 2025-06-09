#ifndef DATASTRUCTUREPROJECT1_POSTFIXTOINFIX_H
#define DATASTRUCTUREPROJECT1_POSTFIXTOINFIX_H

#include <iostream>
#include <cstring>
#include "MyStack.h"
using namespace std;

MyStack<char *> stack2(100);///It is a stack for convert phrase from postfix to infix

bool isExist(string myOperator) {
    string operations[6] = {"^", "*", "/", "%", "+", "-"};
    for (int i = 0; i < 6; i++)
        if (operations[i] == myOperator)
            return true;
    return false;
}

char *convertStringToCharPtr(string &tempStr) {
    int size = tempStr.size();
    char *phrase = (char *) malloc(size + 1);
    strcpy(phrase, tempStr.c_str());
    return phrase;
}

char *concat(string &phrase1, string &phrase2, string &myOperator) {
    char *phrase = (char*) malloc(phrase1.size() + phrase2.size() + myOperator.size() + 1);
    string temp = "(";
    temp.append(phrase1);
    temp.append(myOperator);
    temp.append(phrase2);
    temp.append(")");
    phrase = convertStringToCharPtr(temp);
    return phrase;
}

void postfixToInfix(string* postfix, int& size){
    for (int i = 0; i < size; i++) {
        if (!isExist(postfix[i])) ///It is not operator
            stack2.push(convertStringToCharPtr(postfix[i]));
        else { ///It is operator
            string phrase2 = (string)stack2.pop();
            string phrase1 = (string)stack2.pop();
            string myOperator = postfix[i];
            stack2.push(concat(phrase1, phrase2, myOperator));
        }
    }
}

#endif
