#include <iostream>
#include <algorithm>
#include "InfixToPostfix.h"
#include "PostfixToInfix.h"
using namespace std;

int main(void) {
    cout << "please enter your phrase in the form of infix:\n";
    string phrase;
    getline(cin, phrase);
    phrase.erase(remove(phrase.begin(), phrase.end(), ' '), phrase.end()); ///remove spaces from phrase
    string postfix[phrase.size()]; ///save the postfix form of phrase in this secondaryPostfix
    int size = 0; ///for sizeof postfix phrase
    string operand;///for every operand in the middle of two operator
    string secondaryPostfix[20];///save the postfix form of phrase that after functions such as sin,cos,...
    int secondarySize = 0;///for sizeof secondary postfix
    string tempOperand;
    bool flag = false;
    int openBraces = 0;
    for (int i = 0; i < phrase.size(); i++) {
        if (phrase[i] == '(') {
            stack1.push("(");
            if(isalpha(phrase[i - 1])) { ///sin(45*2) log(10)
                flag = true;
            }
            if (phrase[i + 1] == '-') { ///(-2*)
                if(flag)
                    tempOperand.push_back('-');
                else
                    operand.push_back('-');
                i++;
            }
            if(flag)
                openBraces++;
        }
        else if (phrase[i] == ')') {
            if(flag){
                addToPostfix(tempOperand, secondaryPostfix, secondarySize);
                while (stack1.topValue() != "(") {
                    secondaryPostfix[secondarySize] = (string) stack1.pop();
                    secondarySize++;
                }
                stack1.pop();
                if(openBraces == 1){
                    postfixToInfix(secondaryPostfix, secondarySize);
                    string infixForm = stack2.pop();
                    operand.append(infixForm);
                    flag = false;
                    secondarySize = 0, openBraces = 0;
                    tempOperand.clear(); secondaryPostfix->clear();
                }
                else
                    openBraces--;
           }
            else {
                if (!operand.empty())
                    addToPostfix(operand, postfix, size);
                while (stack1.topValue() != "(") {
                    postfix[size] = (string) stack1.pop();
                    size++;
                }
                stack1.pop();
            }
        }
        else if (!isExist(phrase[i])) {///operand
            if(flag)
                tempOperand.push_back(phrase[i]);
            else
                operand.push_back(phrase[i]);
        }
        else { ///operator
            if (phrase[i] == '-' && i == 0) /// -2+3
                operand.push_back('-');
            if (phrase[i] == '-' && isalpha(phrase[i - 1])){ ///sin-45
                if(flag)
                    tempOperand.push_back('-');
                else
                    operand.push_back('-');
            }
            else if (flag){
                if(!tempOperand.empty())
                    addToPostfix(tempOperand, secondaryPostfix, secondarySize);
                if (phrase[i + 1] == '-') { /// 2+-3
                    tempOperand.push_back('-');
                    checkOperator(phrase[i], secondaryPostfix, secondarySize);//, stack1);
                    i++;
                }
                else
                    checkOperator(phrase[i], secondaryPostfix, secondarySize);//, stack1);
            }
            else {
                if(!operand.empty())
                    addToPostfix(operand, postfix, size);
                if (phrase[i + 1] == '-') { /// 2+-3
                    operand.push_back('-');
                    checkOperator(phrase[i], postfix, size);
                    i++;
                }
                else
                    checkOperator(phrase[i], postfix, size);
            }
        }
    }
    addToPostfix(operand, postfix, size); ///end of phrase
    while (!stack1.isEmpty()) {
        if (stack1.topValue() == "(")
             stack1.pop();
        else {
            postfix[size] = string(stack1.pop());
            size++;
        }
    }
    postfixToInfix(postfix,size);
    cout << "\n";
    cout << "Finally your phrase after putting in parentheses is:\n";
    cout << stack2.pop() << "\n";
}