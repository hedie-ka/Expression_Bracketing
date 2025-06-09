#ifndef DATASTRUCTUREPROJECT1_INFIXTOPOSTFIX_H
#define DATASTRUCTUREPROJECT1_INFIXTOPOSTFIX_H

#include <iostream>
#include "MyStack.h"
#include "PostfixToInfix.h"
using namespace std;

MyStack<char *> stack1(100); ///It is a stack for convert phrase from infix to postfix

bool isExist(char myOperator) {
    char operations[6] = {'^', '*', '/', '%', '+', '-'};
    for (int i = 0; i < 6; i++)
        if (operations[i] == myOperator)
            return true;
    return false;
}

string putInBraces(string phrase) {
    string temp;
    temp.push_back('(');
    for (int i = 0; i < phrase.size(); i++)
        temp.push_back(phrase[i]);
    temp.push_back(')');
    return temp;
}

string putInBracesNumbers(string phrase){
    string newPhrase;
    for (int i = 0; i < phrase.size(); ++i) {
        newPhrase.push_back(phrase[i]);
        if(isalpha(phrase[i]) && (isdigit(phrase[i + 1]) || phrase[i + 1] == '-'))
            newPhrase.push_back('(');
    }
    newPhrase.push_back(')');
    return newPhrase;
}

bool search(string temp, char character){
    for (int i = 0; i < temp.size(); ++i)
        if(temp[i] == character)
            return true;
    return false;
}

void addToPostfix(string &phrase, string *postfix, int &counter) {
    if (!phrase.empty()) { ///checking that phrase is empty or full
        if(isalpha(phrase[1]) && !search(phrase, '(')) ///sin(45) sin(-45)
            phrase = putInBracesNumbers(phrase);
        if ((isalpha(phrase[0]) || phrase[0] == '-') && phrase.size() != 1) ///(-3) (sin90) (log10)
            phrase = putInBraces(phrase);
        postfix[counter] = phrase;
        counter++;
        phrase.clear();
    }
}

void checkOperator(char character, string *postfix, int &counter) { /// ^    * / %     + -
    if (character == '^')
        stack1.push("^");
    else if (character == '*' || character == '/' || character == '%') {
        if (!stack1.isEmpty()) {
            while (stack1.topValue() == "^" || stack1.topValue() == "*"
                   || stack1.topValue() == "/" || stack1.topValue() == "%") {
                string str = stack1.pop();
                addToPostfix(str, postfix, counter);
            }
            if (character == '*')
                stack1.push("*");
            if (character == '/')
                stack1.push("/");
            if (character == '%')
                stack1.push("%");
        }else {
            if (character == '*')
                stack1.push("*");
            if (character == '/')
                stack1.push("/");
            if (character == '%')
                stack1.push("%");
        }
    } else if (character == '+' || character == '-') {
        if (!stack1.isEmpty()) {
            while (stack1.topValue() == "^" || stack1.topValue() == "*"
                   || stack1.topValue() == "/" || stack1.topValue() == "%"
                   || stack1.topValue() == "+" || stack1.topValue() == "-") {
                string str = stack1.pop();
                addToPostfix(str, postfix, counter);
            }
            if (character == '+')
                stack1.push("+");
            if (character == '-')
                stack1.push("-");
        } else {
            if (character == '+')
                stack1.push("+");
            if (character == '-')
                stack1.push("-");
        }
    }
}
#endif
